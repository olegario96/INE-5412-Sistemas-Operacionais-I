/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInvoke_SystemCall.cpp
 * Author: cancian
 * 
 * Created on 18 de Setembro de 2016, 18:10
 */

#include "ModuleInvoke_HardwareEvent.h"
#include "Simul_Entity.h"
#include "Simulator.h"

#include "OperatingSystem.h"
#include "Mediator_HardDisk.h"
#include "Mediator_DMA.h"

#include "Traits.h"


ModuleInvoke_HardwareEvent::ModuleInvoke_HardwareEvent(std::string name) : Module(name) {
    // ...
}

ModuleInvoke_HardwareEvent::ModuleInvoke_HardwareEvent(const ModuleInvoke_HardwareEvent& orig) : Module(orig) {
}

ModuleInvoke_HardwareEvent::~ModuleInvoke_HardwareEvent() {
}

void ModuleInvoke_HardwareEvent::do_run(Entity* entity) {
    std::string method = entity->getAttribute("MethodName")->getValue();
    Simulator* simulator = Simulator::getInstance();

    if (method == "Timer::interrupt_handler()") {
        Timer::interrupt_handler();
        // schedule next timer interruption
        double interruptPeriod = Traits<HW_Timer>::timer_interrupt_period;
        entity->getAttribute("MethodName")->setValue("Timer::interrupt_handler()");
        simulator->insertEvent(simulator->getTnow() + interruptPeriod, this, entity); // this entity never leaves the model
    } else if (method == "HardDisk::interrupt_handler()") {
        HardDisk::interrupt_handler();
        simulator->removeEntity(entity);
    } else if (method == "DMA::interrupt_handler()") {
        DMA::interrupt_handler();
        simulator->removeEntity(entity);
    } else if (method == "MMU::chunk_fault_interrupt_handler()") {
        MMU::chunk_fault_interrupt_handler();
        simulator->removeEntity(entity);
    } else if (method == "MMU::protection_error_interrupt_handler()") {
        MMU::protection_error_interrupt_handler();
        simulator->removeEntity(entity);
    }

  
    
}
