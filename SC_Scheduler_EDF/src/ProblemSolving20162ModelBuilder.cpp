/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProblemSolving20162ModelBuilder.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 08:49
 */

#include "ProblemSolving20162ModelBuilder.h"

#include "OperatingSystem.h"
#include "Traits.h"

#include "Simulator.h"
#include "Simul_Entity.h"
#include "SourceModule.h"
#include "ModuleCreate.h"
#include "ModuleDispose.h"
#include "ModuleInvoke_PulseExecution.h"

ProblemSolving20162ModelBuilder::ProblemSolving20162ModelBuilder() {
}

ProblemSolving20162ModelBuilder::ProblemSolving20162ModelBuilder(const ProblemSolving20162ModelBuilder& orig) {
}

ProblemSolving20162ModelBuilder::~ProblemSolving20162ModelBuilder() {
}

Model * ProblemSolving20162ModelBuilder::buildModel() {
    Model* model = new Model("Operating Systems Simulation 2016: Computational System Theme 1");

    //Traits<Model>::ProblemType problemType = Traits<Model>::problemType;
    //Traits<Model>::ProblemSolving problem = Traits<Model>::problemChoosen;

    ModuleCreate* createPulse = new ModuleCreate("Create pulse", 0.0, 1, "1.0", "pulse", true, 1); // one single entity is created
    model->addSourceModule((SourceModule*) createPulse);
    
    ModuleInvoke_PulseExecution* pulseExecution = new ModuleInvoke_PulseExecution("Execute pulse");
    model->addModule(pulseExecution);
    
    //ModuleDelay* delayPulse = new ModuleDelay("Delay pulse", "1");
    //model->addModule(delayPulse);

    ModuleDispose* disposePulse = new ModuleDispose("Terminate pulse", false);
    model->addModule(disposePulse);
    
    // connect the model
    createPulse->addNextModule(pulseExecution);
    //pulseExecution->addNextModule(delayPulse);
    pulseExecution->addNextModule(disposePulse);
    //delayPulse->addNextModule(pulseExecution);
    //
    //createTimerInterrupt->addNextModule(disposeTimerInterrupt);
    

    // entity attributes
    model->addEntityAttribute(new Attribute("MethodName", ""));
    model->addEntityAttribute(new Attribute("ExecutionStep", "0"));    

    // time infos
    model->setReplicationLength(Traits<Model>::simulationLength);
    model->setWarmUpPeriod(0);
    model->setTimeUnitBase(Util::TimeUnit::milisecond);

    return model;
}

/*   
   // create modules for process and thread life cycle
   double firstCreation = Traits<Model>::firstCreation;
   ModuleCreate* createProcess = new ModuleCreate("Create Process", firstCreation, 0, std::to_string(Traits<Process>::timeBetweenCreations), "Process", 1);
   model->addSourceModule((SourceModule*) createProcess);
    
   ModuleInvoke_MemoryAlloc* allocateMemory = new ModuleInvoke_MemoryAlloc("Allocate Memory");
   model->addModule(allocateMemory);

   double delayTime = Simulator::generate_uniform_distribution(Traits<Thread>::minCpuBurst, Traits<Thread>::maxCpuBurst);
   //std::string delayTme = "unif("+std::to_string(Traits<Thread>::minCpuBurst) +","+ std::to_string(Traits<Thread>::maxCpuBurst)+")"; 
   ModuleDelay* delayProcess = new ModuleDelay("Execute Process", std::to_string(delayTime));
   model->addModule(delayProcess);
    
   ModuleInvoke_MemoryDealloc* deallocateMemory = new ModuleInvoke_MemoryDealloc("Free Memory");
   model->addModule(deallocateMemory);
    
   ModuleDispose* disposeProcess = new ModuleDispose("Terminate Process", false);
   model->addModule(disposeProcess);

   // connect modules for process
   createProcess->addNextModule(allocateMemory);
   allocateMemory->addNextModule(delayProcess);
   allocateMemory->addNextModule(disposeProcess);
   delayProcess->addNextModule(deallocateMemory);
   deallocateMemory->addNextModule(disposeProcess);
    
   // entity attributes
   model->addEntityAttribute(new Attribute("ChunkPtr", "0"));
        
   // time infos
   model->setReplicationLength(Traits<Model>::simulationLength);
   model->setWarmUpPeriod(0);
   model->setTimeUnitBase(Util::TimeUnit::milisecond);
   return model;    
}
 */






/*
 
     
    
    
    
    // create modules for timer interrupt
    double timerPeriod = Traits<Timer>::timer_interrupt_period;
    ModuleCreate* timerInterruptCreate = new ModuleCreate("Timer", timerPeriod, 0, std::to_string(timerPeriod), "Timer Interruption",false, 1);
    model->addSourceModule((SourceModule*) timerInterruptCreate);
    
    ModuleInvoke_InterruptHandler* invokeTimerHandler = new ModuleInvoke_InterruptHandler("InvokeTimerInterruptHandler");
    model->addModule(invokeTimerHandler);
    
    ModuleDispose* timerInterruptDeparture = new ModuleDispose("TimerInterruptEnd", false);
    model->addModule(timerInterruptDeparture);
    
    // connect modules of timer interrupt
    timerInterruptCreate->addNextModule(invokeTimerHandler);
    invokeTimerHandler->addNextModule(timerInterruptDeparture);

    /*
    // create modules for HD interrupt
    double timerPeriod = Traits<CPU>::timer_interrupt_period;
    ModuleCreate* timerInterruptCreate = new ModuleCreate("Timer", timerPeriod, 0, std::to_string(timerPeriod), "Timer Interruption", 1);
    model->addSourceModule((SourceModule*) timerInterruptCreate);
    ModuleInvoke_InterruptHandler* invokeTimerHandler = new ModuleInvoke_InterruptHandler("InvokeTimerInterruptHandler");
    model->addModule(invokeTimerHandler);
    ModuleDispose* timerInterruptDeparture = new ModuleDispose("TimerInterruptEnd", false);
    model->addModule(timerInterruptDeparture);
    // connect modules of timer interrupt
    timerInterruptCreate->addNextModule(invokeTimerHandler);
    invokeTimerHandler->addNextModule(timerInterruptDeparture);
 * /  


    // create modules for process and thread life cycle
    double firstCreation = Traits<Model>::firstCreation;
    ModuleCreate* createProcess = new ModuleCreate("CreateProcess", firstCreation, 0, std::to_string(Traits<Process>::timeBetweenCreations), "Process", true, 1);
    model->addSourceModule((SourceModule*) createProcess);  
        
    ModuleInvoke_MemoryAlloc* allocateMemory = new ModuleInvoke_MemoryAlloc("Allocate Memory");
    model->addModule(allocateMemory);
    
    ModuleInvoke_ProcessExec* invokeProcessExec = new ModuleInvoke_ProcessExec("InvokeProcessExec");
    model->addModule(invokeProcessExec);
    
    ModuleInvoke_ThreadExec* invokeThreadExec = new ModuleInvoke_ThreadExec("InvokeThreadExec");
    model->addModule(invokeThreadExec);
    
    ModuleInvoke_FileSystem* invokeFileSystem = new ModuleInvoke_FileSystem("InvokeFileSystem");
    model->addModule(invokeFileSystem);
    
    ModuleInvoke_DiskScheduler* invokeDiskScheduler = new ModuleInvoke_DiskScheduler("InvokeDiskScheduler");
    model->addModule(invokeDiskScheduler);
    
    ModuleWait* waitProcessExit = new ModuleWait("WaitForProcessToEnd", "Process_Exit", "ProcessPtr", 1);
    model->addModule(waitProcessExit);
    
    ModuleSignal* signalProcessExit = new ModuleSignal("SignalProcessEnd", "Process_Exit");
    model->addModule(signalProcessExit);
    
    ModuleDispose* disposeThread = new ModuleDispose("DisposeThread", false);
    model->addModule(disposeThread);

    ModuleInvoke_MemoryDealloc* deallocateMemory = new ModuleInvoke_MemoryDealloc("Free Memory");
    model->addModule(deallocateMemory);
    
    ModuleDispose* disposeProcess = new ModuleDispose("DisposeProcess", false);
    model->addModule(disposeProcess);
    
    // connect modules for process
    createProcess->addNextModule(allocateMemory);
    allocateMemory->addNextModule(invokeProcessExec);
    invokeProcessExec->addNextModule(waitProcessExit);
    waitProcessExit->addNextModule(disposeProcess);   // connection to invokeDiskScheduler is implicit inside invokeProcessExec (??))
    invokeThreadExec->addNextModule(disposeThread);  
    invokeThreadExec->addNextModule(signalProcessExit); // second next (when process is finishing)
    invokeThreadExec->addNextModule(invokeDiskScheduler);  // third next (when thread will access disk and filesystem)
    invokeDiskScheduler->addNextModule(invokeFileSystem);
    invokeFileSystem->addNextModule(invokeThreadExec);
    signalProcessExit->addNextModule(deallocateMemory);
    deallocateMemory->addNextModule(disposeThread);
    

    // entity attributes
    //model->addEntityAttribute(new Attribute("MethodToInvoke", ""));
    model->addEntityAttribute(new Attribute("NumThreads", "0"));
    model->addEntityAttribute(new Attribute("ProcessPtr", "0"));
    model->addEntityAttribute(new Attribute("ThreadPtr", "0"));
    model->addEntityAttribute(new Attribute("ThreadNum", "0"));
    model->addEntityAttribute(new Attribute("RemainingExecutionTime", "0"));
    model->addEntityAttribute(new Attribute("ExecutionStage", "0"));
    model->addEntityAttribute(new Attribute("CPUBursts", "0"));
    for (int i = 2; i <= Traits<Thread>::maxThreadsPerProcess; i++) {
        model->addEntityAttribute(new Attribute("Child" + std::to_string(i), "0"));
    }
    model->addEntityAttribute(new Attribute("ChunkPtr", "0"));

 
 */