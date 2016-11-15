/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInvoke_PulseExecution.cpp
 * Author: cancian
 * 
 * Created on 18 de Setembro de 2016, 12:06
 */

#include "ModuleInvoke_PulseExecution.h"

#include "Simulator.h"
#include "Simul_Debug.h"

#include "OperatingSystem.h"
#include "Mediator_Timer.h"
#include "HW_Machine.h"

ModuleInvoke_PulseExecution::ModuleInvoke_PulseExecution(std::string name) : Module(name) {
}

ModuleInvoke_PulseExecution::ModuleInvoke_PulseExecution(const ModuleInvoke_PulseExecution& orig) : Module(orig) {
}

ModuleInvoke_PulseExecution::~ModuleInvoke_PulseExecution() {
}

void ModuleInvoke_PulseExecution::do_run(Entity* entity) { // virtual
    Simulator* simulator = Simulator::getInstance();
    Debug::cout(Debug::Level::fine, this, entity, "Pulsing execution");

    if (IsFirstPulse()) { // hate this here, but it's simpler...  (can't do it inside Timer constructor since simulation has not began and therefore there is no actualEntity)
        Entity* interruptEntity = simulator->createEntity();
        interruptEntity->getAttribute("EntityType")->setValue("TimerInterruption");
        interruptEntity->getAttribute("MethodName")->setValue("Timer::interrupt_handler()");
        simulator->insertEvent(Traits<HW_Timer>::timer_interrupt_period, HW_Machine::Module_HardwareEvent(), interruptEntity);
    }
    HW_Machine::CPU()->pulse();
    //Module* nextModule = *(this->_nextModules->begin());
    simulator->insertEvent(simulator->getTnow()+1.0, this, entity);
}