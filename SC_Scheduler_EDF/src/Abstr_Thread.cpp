/*
 * File:   Thread.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 10:30 AM
 */

#include "Abstr_Thread.h"
#include "Simul_Debug.h"
#include "OperatingSystem.h"
#include "Simulator.h"
#include "Mediator_CPU.h"
#include <stdlib.h>

Thread* Thread::_running;

Thread::Thread(Process* task, Thread::State state) {
    _id = Thread::getNewId();
    _process = task;
    _state = state;
    // INSERT YOUR CODE HERE
    // ...
    //_queue = new Queue<Thread*>();
    _queue = new std::list<Thread*>();
    _accountInfo._arrivalTime = Simulator::getInstance()->getTnow();
    _accountInfo._cpuTime = 0;
    _accountInfo._waitingTime = 0;
    _accountInfo._blockedTime = 0;
    _accountInfo._dispatchedTime = 0;
    _accountInfo._deadLineTime = Simulator::getInstance()->getTnow() + DEAD_LINE;
    _accountInfo._priority = Simulator::getInstance()->getTnow() + DEAD_LINE;
}

Thread::Thread(const Thread& orig) {
}

Thread::~Thread() = default;

Thread* Thread::running() {
    return _running;
    //return System::scheduler()->choosen();
}

Process* Thread::getProcess() {
    return _process;
}

int Thread::getPriority() const {
    return _accountInfo._priority;
}

void Thread::sleep(Queue<Thread*> * q) {
    Debug::cout(Debug::Level::trace, "Thread::sleep(" + std::to_string(reinterpret_cast<unsigned long> (q)) + ")");
    // INSERT YOUR CODE HERE

    auto running_thread = running();
    // calcula quanto tempo ficou executando
    auto executing_time = (Simulator::getInstance()->getTnow() - running_thread->_accountInfo._cpuAux);
    running_thread->_accountInfo._cpuTime += executing_time;
    // anota o horário que ela ficou bloqueada
    running_thread->_accountInfo._blockedAux = Simulator::getInstance()->getTnow();
    // vai para o estado de espera (bloqueada)
    running_thread->_state = WAITING;
    // põe na fila de bloqueadas
    q->insert(&running_thread);
    // chama o escalonador
    auto scheduler = OperatingSystem::Process_Scheduler();
    // escolhe uma nova thread
    auto next_thread = scheduler->choose();
    dispatch(running_thread, next_thread);
}

void Thread::wakeup(Queue<Thread*> * q) {
    Debug::cout(Debug::Level::trace, "Thread::wakeup(" + std::to_string(reinterpret_cast<unsigned long> (q)) + ")");
    // INSERT YOUR CODE HERE
    // ...
    // verifica quem é a primeira thread na lista de bloqueadas
    auto unlocked_thread = q->front();
    // tira da fila de bloqueadas
    q->pop();
    // põe no estaddo de pronta
    unlocked_thread->_state = READY;
    // calcula quanto tempo ficou bloqueada
    unlocked_thread->_accountInfo._blockedTime += (Simulator::getInstance()->getTnow() - unlocked_thread->_accountInfo._blockedAux);
    // Anota o horário que ela foi pro estado de pronto
    unlocked_thread->_accountInfo._waitAux = Simulator::getInstance()->getTnow();
    // chamar o escalonador
    auto scheduler = OperatingSystem::Process_Scheduler();
    // coloca ela na fila de prontos
    scheduler->insert(unlocked_thread);
    // escolhe uma nova thread
    auto new_running = scheduler->choose();
    dispatch(_running, new_running);
}

/**
 * Threads podem decidir deixar a CPU invocando a chamada void Thread::yield(), que precisa ser implementada. A implementação
 * dessa chamada deve colocar a thread que está executando no estado READY, incluí-la na fila de threads prontas, chamar
 * o escalonador para escolher outra thread, invocando Thread* Scheduler::choose() e então o despachador para iniciar
 * a execução da thread escolhida pelo escalonador, invocando static void Thread::dispatch(Thread* previous, Thread* next).
 **/
void Thread::yield() {
    Debug::cout(Debug::Level::trace, "Thread::yield()");
    // INSERT YOUR CODE HERE
    // ...

    // colocar a thread que está executando no estado READY
    _running->_state = READY;
    // incluí-la na fila de threads prontas
    auto scheduler = OperatingSystem::Process_Scheduler();
    scheduler->insert(_running);
    // calcula quanto tempo ficou executando
    _running->_accountInfo._cpuTime += (Simulator::getInstance()->getTnow() - _running->_accountInfo._cpuAux);
    // anota o horário que ficou pronta
    _running->_accountInfo._waitAux = Simulator::getInstance()->getTnow();
    // chamar o escalonador para escolher outra thread
    auto new_running = scheduler->choose();
    // chamar despachador para iniciar a execução da thread escolhida pelo escalonador
    dispatch(_running, new_running);
}

/**
 * Threads aguardarão pelo término de outras threads quando for invocada a chamada void Thread::join(), que precisa ser
 * implementada. A implementação dessa chamada deve verificar se a thread this está no estado FINISHING
 * ou não. Se estiver, então a thread que invocou a chamada (a que está executando --running--) simplesmente continua sua execução.
 * Se não estiver, então a thread executando deve ser colocada no estado WAITING e colocada na fila de threads esperando pela
 * thread this. Ainda nesse caso, deve-se chamar o escalonador para escolher outra thread, invocando Thread* Scheduler::choose()
 * e então o despachador para iniciar a execução da thread escolhida pelo escalonador, invocando
 * static void Thread::dispatch(Thread* previous, Thread* next). Para melhor ilustrar essa chamada, se o código da thread T1
 * tiver a chamada T2->join(), então T1 é quem está executando (running) e T2 é quem foi invocada (this), e é T1 que deve ser
 * bloqueada esperando por T2 (se T2 não estiver FINISHING).
 **/
int Thread::join() {
    Debug::cout(Debug::Level::trace, "(" + std::to_string(reinterpret_cast<unsigned long> (this)) + ") Thread::join()");
    // INSERT YOUR CODE HERE
    // ...

    // verificar se a thread this está no estado FINISHING ou não
    if (!(this->_state == FINISHING)) {
        // Se não estiver, então a thread chamada deve ser colocada no estado WAITING
        _running->_state = WAITING;
        // calcula quanto tempo ficou executando
        _running->_accountInfo._cpuTime += (Simulator::getInstance()->getTnow() - _running->_accountInfo._cpuAux);
        // anota o horário que ficou bloqueada
        _running->_accountInfo._blockedAux = Simulator::getInstance()->getTnow();
        // e colocada na fila de threads esperando pela thread this
        this->getQueue()->push_back(_running);
        // chamar o escalonador para escolher outra thread
        auto scheduler = OperatingSystem::Process_Scheduler();
        auto new_running = scheduler->choose();
        // chamar despachador para iniciar a execução da thread escolhida pelo escalonador
        dispatch(_running, new_running);
    }
}

/**
 * Threads serão finalizadas quando for invocada a chamada void Thread::exit(), que precisa ser implementada. A implementação
 * dessa chamada deve colocar a thread que está executando no estado FINISHING, verificar se há alguma thread na lista
 * de threads bloqueadas esperando por essa thread. Se houver, todas as threads na lista devem ser colocadas no estado
 * READY e colocadas na fila de threads prontas para executar. Em qualquer caso, deve-se ainda chamar o escalonador para
 * escolher outra thread, invocando Thread* Scheduler::choose() e então o despachador para iniciar a execução da thread
 * escolhida pelo escalonador, invocando static void Thread::dispatch(Thread* previous, Thread* next).
 **/
void Thread::exit(int status) { /* static */
    Debug::cout(Debug::Level::trace, "Thread::exit(" + std::to_string(status) + ")");
    // INSERT YOUR CODE HERE
    // ...
    // colocar a thread que está executando no estado FINISHING

    _running->_state = FINISHING;
    _running->_accountInfo._priority = IDLE;
    auto scheduler = OperatingSystem::Process_Scheduler();
    // verificar se há alguma thread na lista de threads bloqueadas esperando por essa thread.
    for (auto i = getThreadsList()->front(); i != getThreadsList()->back(); ++i) {
        // Se houver, todas as threads na lista devem ser colocadas no estado READY
        if (i->_state == WAITING) {
            i->_state = READY;
            // calcula quanto tempo ficou esperando (bloqueada)
            i->_accountInfo._blockedTime += (Simulator::getInstance()->getTnow() - i->_accountInfo._blockedAux);
            // anota o horário que ficou pronta
            i->_accountInfo._waitAux = Simulator::getInstance()->getTnow();
            // colocadas na fila de threads prontas para executar
            scheduler->insert(i);
        }
    }
    // chamar o escalonador para escolher outra thread
    auto new_running = scheduler->choose();
    // chamar despachador para iniciar a execução da thread escolhida pelo escalonador
    dispatch(_running, new_running);

}

/**
 * Threads são despachadas, ou seja, têm seus contextos trocados, quando se invoca a chamada
 * static void Thread::dispatch(Thread* previous, Thread* next), que precisa ser implementada. A implementaçao desse  método
 * deve inicialmente verificar se a próxima thread (next) é nula ou não. Se for, nada precisa ser feito (isso só ocorre quando
 * a fila de prontos é vazia e não há thread para ser escalonada). Se não for, então o atributo _running deve ser atualizado e
 * a thread a ser executada precisa ser colocada no estado RUNNING e retirada da fila de prontos. Então deve ser verificado se a thread anterior
 * (previous) é diferente de nula e também se é diferente da próxma thread. Se não for, então basta restaurar o contexto da
 * próxima thread, invocando static void CPU::restore_context(Thread* next). Se for, então é preciso verificar se a thread
 * anterior estava no estado RUNNING e caso sim, então a thread anterior deve passar para o estado READY. Após esse teste
 * deve-se fazer a troca de contexto entre as threads, invocando o método static void CPU::switch_context(Thread* previous, Thread* next).
 * **/
void Thread::dispatch(Thread* previous, Thread* next) {
    Debug::cout(Debug::Level::trace, "Thread::dispatch(" + std::to_string(reinterpret_cast<unsigned long> (previous)) + "," + std::to_string(reinterpret_cast<unsigned long> (next)) + ")");
    // INSERT YOUR CODE HERE
    // ...
    double tnow = Simulator::getInstance()->getTnow();
    // o atributo _running deve ser atualizado
    _running = next;
    // verificar se a próxima thread (next) é nula ou não. Se for, nada precisa ser feito
    if (next != nullptr) {
        // a thread a ser executada precisa ser colocada no estado RUNNING
        next->_state = Thread::State::RUNNING;
        // calcula quanto tempo ficou esperando
        next->_accountInfo._waitingTime += (Simulator::getInstance()->getTnow() - next->_accountInfo._waitAux);
        // anota o horário que começou a rodar
        next->_accountInfo._cpuAux = Simulator::getInstance()->getTnow();
        next->_accountInfo._dispatchedTime = tnow;
        // e retirada da fila de prontos
//@TODO: SOLVE REFERENCE PROBLEM
        Scheduler<Thread>* sch = OperatingSystem::Process_Scheduler();
        sch->remove(next);
        Thread* t = sch->choose();
        //OperatingSystem::Process_Scheduler()->remove(next);
        // deve ser verificado se a thread anterior (previous) é diferente de nula e também se é diferente da próxma thread
        if ((previous != nullptr) && (previous != next)) {
            // ter seus atributos atualizados
            previous->_accountInfo._priority = previous->_accountInfo._priority * 0.5 + (tnow - previous->_accountInfo._dispatchedTime)*0.5;
            //  verificar se a thread anterior estava no estado RUNNING
            if (previous->_state == Thread::State::RUNNING) {
                // a thread anterior deve passar para o estado READY
                previous->_state = Thread::State::READY;
                //  e ser colocada na fila de prontos
                sch->insert(next);
//@TODO: SOLVE REFERENCE PROBLEM
////               OperatingSystem::Process_Scheduler()->insert(previous);
            }
            // fazer a troca de contexto entre as threads
            //CPU::switch_context(previous, next);
        } else {
            // Se não for, então basta restaurar o contexto da próxima thread
            //CPU::restore_context(next);
        }
    }
}

/**
 * Threads criarão novas threads quando for invocada a chamada static void Thread::thread_create(), que precisa ser
 * implementada. A implementação dessa chamada deve criar um objeto Thread, inicializar seus novos atributos, colocá-la na
 * lista de threads no sistema, inseri-la na fila de prontos inovando o método void Scheduler::insert(Thread* thread), e
 * se o escalonador for preemptivo chamar
 * o escalonador para escolher outra thread, invocando Thread* Scheduler::choose() e então o despachador para iniciar a
 * execução da thread escolhida pelo escalonador, invocando static void Thread::dispatch(Thread* previous, Thread* next).
 **/
Thread* Thread::thread_create(Process* parent) {
    Debug::cout(Debug::Level::trace, "Thread::create(" + std::to_string(reinterpret_cast<unsigned long> (parent)) + ")");
    // INSERT YOUR CODE HERE
    // ...

    // criar um objeto Thread
    Thread* newThread = new Thread(parent, READY);

    // inicializar seus novos atributos
    // ...
    // anota o horário que ficou pronta
    newThread->_accountInfo._waitAux = Simulator::getInstance()->getTnow();
    // colocá-la na  lista de threads no sistema
    auto list_threads = getThreadsList();
    list_threads->push_back(newThread);
        // inseri-la na fila de prontos
        auto scheduler = OperatingSystem::Process_Scheduler();
        scheduler->insert(newThread);
        // se escalonador for preemptivo
        if (scheduler->getPreemptive()) {
            // chamar o escalonador para escolher outra thread
            auto new_running = scheduler->choose();
            // invocar o despachador
            dispatch(_running, new_running);
        }

    Debug::cout(Debug::Level::fine, "Created thread " + std::to_string(reinterpret_cast<unsigned long> (newThread)));
    return newThread;
}

int Thread::getDeadLineTime() {
    return _accountInfo._deadLineTime;
}