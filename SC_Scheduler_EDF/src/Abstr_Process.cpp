/*
 * File:   Process.cpp
 * Author: cancian
 *
 * Created on August 31, 2015, 7:49 AM
 */

#include "Simul_Debug.h"
#include "Abstr_Process.h"
#include "Abstr_Thread.h"
#include "OperatingSystem.h"
#include "Simulator.h"
#include "Simul_Debug.h"
#include "Abstr_MemoryManager.h"
#include "Abstr_Scheduler.h"

Process::Process(unsigned int parentId) {
    this->_entity = Simulator::getInstance()->getEntity(); // simulation purposes only
    this->_entity->setPointer(this); // simulation purposes only

    this->_idInfo._processId = Process::getNewId();
    this->_idInfo._parentId = parentId;
    this->_idInfo._priority = Simulator::generate_uniform_distribution(0, 10);
    this->_memInfo._chunks = new std::list<MemoryChunk*>();
    // random memory info about the new process
    unsigned int numSegments = Simulator::generate_uniform_distribution(2, 5);
    unsigned long lastLogicalAddress;
    unsigned int size;
    for (unsigned int i = 0; i < numSegments; i++) {
        size = Simulator::generate_uniform_distribution(250 / (numSegments + 3), 250 / numSegments);
        MemoryChunk* logicalChunk = new MemoryChunk(lastLogicalAddress, size, false, false, false); // logical chunks that have to be allocated into memory
        _memInfo._chunks->insert(_memInfo._chunks->begin(), logicalChunk);
        lastLogicalAddress += size;
    }
    // INSERT YOUR CODE HERE
    // ...
    _cpuTime._CPUTime = 0;
}

Process::Process(const Process& orig) {
}

Process::~Process() = default;

unsigned int Process::getParentId() const {
    return _idInfo._parentId;
}

unsigned int Process::getId() const {
    return _idInfo._processId;
}


/**
 * Processos chegarão ao sistema quando for invocada a chamada static Process* Process::exec(), que precisa
 * ser implementada. A implementação dessa chamada de sistema deve criar um Process, alocar memória para ele invocando
 * a chamada de sistema void MemoryManagement::alloc(Process* process), inicializar seus atributos, colocá-lo na lista
 * de processos no sistema e criar uma thread (correspondente a "main") para esse processo invocando a chamada
 * static void Thread::thread_create(Process* parent). O metodo retorna o processo criado.
 **/
Process* Process::exec() { /*static*/
    Debug::cout(Debug::Level::trace, "Process::exec()");
    // INSERT YOUR CODE HERE (just complete what is missing... easy this time...)

    // criar um Process
    Process* newProcess = new Process(0);

    // alocar memória para ele
    auto memory_manager = OperatingSystem::Memory_Manager();
    memory_manager->allocateMemory(sizeof(newProcess));

    // inicializar seus atributos
    // ...
    newProcess->_cpuTime._CPUTime = 0;
    newProcess->_cpuTime._waitingTime = 0;
    newProcess->_cpuTime._dispatchedTime = 0;
    newProcess->_cpuTime._blockedTime = 0;

    // colocá-lo na lista de processos no sistema
    auto list_proc = getProcessesList();
    list_proc->push_back(newProcess);

    // criar uma thread (correspondente a "main") para esse processo
    auto thread_main = Thread::thread_create(newProcess);

    // retorna o processo criado
    return newProcess;
}

/**
 * Processos serão finalizados quando for invocada a chamada static void Process::exit(int status = 0), que precisa ser
 * implementada. A implementação dessa chamada deve desalocar a memória do processo invocando
 * void MemoryManagement::desalloc(Process* process), excluir todas as threads desse processo, excluir o processo (destruir
 * o objeto Process), invocar o escalonador para escolher outra thread, invocando Thread* Scheduler::choose() e então
 * o despachador para iniciar a execução da thread escolhida pelo escalonador, invocando
 * void Thread::dispatch(Thread* previous, Thread* next).
 **/
void Process::exit(int status) { /*static*/
    Debug::cout(Debug::Level::trace, "Process::exit(" + std::to_string(status) + ")");
    // INSERT YOUR CODE HERE (Now it's up to you...)
    // ...

    // desalocar a memória do processo
    auto memory_manager = OperatingSystem::Memory_Manager();
    auto run = Thread::running();
    auto delete_proc = run->getProcess();
    auto front = delete_proc->_memInfo._chunks->front();

    while (front != nullptr) {
        delete_proc->_memInfo._chunks->pop_front();
        memory_manager->deallocateMemory(front);
        front = delete_proc->_memInfo._chunks->front();
    }
    

    // excluir todas as threads desse processo
    for (auto i = run->_queue->begin(); i != run->_queue->end(); ++i) {  
        if ((*i)->getProcess() == delete_proc) {
            delete_proc->_cpuTime._CPUTime += (*i)->_accountInfo._cpuTime;
            delete_proc->_cpuTime._waitingTime += (*i)->_accountInfo._waitingTime;
            delete_proc->_cpuTime._dispatchedTime += (*i)->_accountInfo._dispatchedTime;
            delete_proc->_cpuTime._blockedTime += (*i)->_accountInfo._blockedTime;
            (*i)->exit(status);
        }
    }

    // excluir o processo
    auto simul_list = Simulator::getAllProc();
    simul_list->push_back(delete_proc);
    (getProcessesList())->remove(delete_proc);

    // invocar o escalonador para escolher outra thread
    auto scheduler = OperatingSystem::Process_Scheduler();
    Thread* next_thread = scheduler->choose();

    // invocar o despachador para iniciar a execução da thread escolhida
    Thread::dispatch(nullptr, next_thread);
}