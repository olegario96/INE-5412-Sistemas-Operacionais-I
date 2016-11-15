/*
 * File:   System.cpp
 * Author: cancian
 *
 * Created on October 9, 2015, 9:04 PM
 */
#include <string>

#include "OperatingSystem.h"
#include "Application.h"
#include "HW_CPU.h"
#include "HW_Machine.h"
#include "Simulator.h"

void OperatingSystem::LoadApplication(Application* app, MMU::PhysicalAddress address) {
    Debug::cout(Debug::Level::trace, "OperatingSystem::LoadApplication(" + std::to_string(reinterpret_cast<unsigned long> (app)) + "," + std::to_string(address) + ")");
    std::list<Application::Information> code = app->getCode();
    HW_MMU::Information info;
    for(std::list<HW_MMU::Information>::iterator it = code.begin(); it != code.end(); it++) {
        info = (*it);
        HW_Machine::RAM()->write(address, info);
        address++;
    }
}

void OperatingSystem::SetBootApplication(Application* app) {
    Debug::cout(Debug::Level::trace, "OperatingSystem::SetBootApplication(" + std::to_string(reinterpret_cast<unsigned long> (app)) + ")");
    HW_CPU::Register address = HW_Machine::CPU()->readRegister(HW_CPU::pc);
    LoadApplication(app, address);
}


void OperatingSystem::Init() {
    Debug::cout(Debug::Level::trace, "OperatingSystem::init()");
    HW_Machine::Init();

    OperatingSystem::CPU_Mediator();
    OperatingSystem::DMA_Mediator();
    OperatingSystem::HardDisk_Mediator();
    OperatingSystem::MMU_Mediator();
    OperatingSystem::Timer_Mediator();

    SetBootApplication(Application::DefaultBootApplication());  // load boot application into RAMs
}

void OperatingSystem::ExecuteTestCode() {
    Debug::cout(Debug::Level::trace, "OperatingSystem::EXecuteTestCode()");
    Simulator* simulator = Simulator::getInstance();
    Entity* entity = simulator->getEntity();
    Module* module = simulator->getModule();
    int executionStep = std::stoi(entity->getAttribute("ExecutionStep")->getValue());
    double timeNow = simulator->getTnow();

    // INSERT HERE YOUR CODE
    // You can write a test code that will be executed and will invoke system calls or whenever you want
    // Follow the examples...
    // ...

    Process *proc_1;
    Process *proc_2;
    Thread *thread_1;
    Thread *thread_2;
    Queue<Thread*> q;
    int id;
    int i = 0;
    switch (executionStep) {
        case 0:  // ExecutionStep is initialized with 0
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++)); // advance execution step
            simulator->insertEvent(timeNow + 10.0, module, entity); // future event when execution will advance
            std::cout << "[TEST #1]Creating process...\n";
            proc_1 = Process::exec();
            std::cout << "Process " << proc_1->getId() << " created!\n";
        case 1:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++)); // advance execution step
            std::cout << "[TEST #2]Creating thread...\n";
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            std::cout << "Thread " << thread_1->getId() << " created!\n";
        case 2:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++)); // advance execution step
            std::cout << "[TEST #3]Thread yield...\n";
            std::cout << "Creating thread... \n";
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            thread_1->yield();
            std::cout << "Thread " << thread_1->getId() << " executed yield.\n";
        case 3:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++)); // advance execution step
            std::cout << "[TEST #4]Thread join...\n";
            std::cout << "Creating threads...";
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            thread_2 = Thread::thread_create(proc_1);
            std::cout << "Thread " << thread_1->getId() << " and " << thread_2->getId() << " belongs to the process " << proc_1->getId() << "\n";
            thread_1->join();
            std::cout << "Thread " << thread_1->getId() << " executed join!\n";
        case 4:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++));
            std::cout << "[TEST #5]Process exit...\n";
            std::cout << "Creating threads...\n";
            proc_1 = Process::exec();
            proc_2 = Process::exec();
            id = proc_1->getId();
            thread_1 = Thread::thread_create(proc_1);
            thread_2 = Thread::thread_create(proc_2);
            proc_1->exit();
            std::cout << "Process " << id  << " executed exit!\n";
        case 5:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++));
            std::cout << "[TEST #6] Thread Exit\n";
            std::cout << "Creating thread...\n";
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            thread_2 = Thread::thread_create(proc_1);
            std::cout << "Trying to exit Thread : " << thread_1->getId() << "\n";
            id = thread_1->getId();
            thread_1->exit();
            std::cout << "Thread " << id << " executed exit!\n";
        case 6:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++));
            std::cout << "[TEST #7] Thread sleep\n";
            std::cout << "Creating thread...\n";
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            thread_1->sleep(&q);
            std::cout << "Thread " << thread_1->getId() << " executed sleep!\n";

        case 7:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++));
            std::cout << "[TEST #8] Thread wakeup\n";
            std::cout << "Creating thread...\n";
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            thread_1->sleep(&q);
            std::cout << "Thread " << thread_1->getId() << " executed sleep!\n";
            thread_1->wakeup(&q);
            std::cout << "Thread " << thread_1->getId() << " executed wakeup!\n";

        case 8:
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(executionStep++));
            std::cout << "[TEST #9] Reschedule\n";
            auto scheduler = OperatingSystem::Process_Scheduler();
            proc_1 = Process::exec();
            thread_1 = Thread::thread_create(proc_1);
            thread_2 = Thread::thread_create(proc_1);
            scheduler->reschedule();
            auto new_thread = scheduler->choose();
            std::cout << "Thread " << new_thread->getId() << " scheuled!\n";
            goto TheEnd;
    }

    TheEnd: ;

}

 /*
  Not used
  */
 HW_MMU::Information OperatingSystem::asmm(std::string mnemonic) {
     HW_MMU::Information bincode;
     /* @TODO
      */
     if (mnemonic == "Process:exec()") {
         bincode = 0xFFFFFFFF; // - (HW_CPU::addi<<24) +
     }
     //@TODO
     bincode = (HW_CPU::addi<<26) + (HW_CPU::s0<<21) + (HW_CPU::s1<<16) + 1; // for tests purpose only
     return bincode;
 }

 /*

    thread exit
    escalonamento
    testes

  */