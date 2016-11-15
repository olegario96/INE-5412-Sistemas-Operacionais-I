/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Continuous.cpp
 * Author: cancian
 * 
 * Created on 23 de Setembro de 2016, 16:25
 */

#include "Mediator_MMU.h"
#include "HW_Machine.h"
#include "HW_MMU_Continuous.h"

#include "Simulator.h"

HW_MMU_Continuous::HW_MMU_Continuous() {
    // INSERT YOUR CODE HERE
    // ...
 }

HW_MMU_Continuous::HW_MMU_Continuous(const HW_MMU_Continuous& orig) {
}

HW_MMU_Continuous::~HW_MMU_Continuous() {
}

HW_MMU_Continuous::Register HW_MMU_Continuous::readRegister(unsigned int registerNum) {
    if (registerNum==0) {
        return this->_base;
    } else if (registerNum==1) {
        return this->_limit;
    }
    return 0;
}

void HW_MMU_Continuous::writeRegister(unsigned int registerNum, HW_MMU_Continuous::Register value) {
    if (registerNum==0) {
        this->_base = value;
    } else if (registerNum==1) {
        this->_limit = value;
    }
}

HW_MMU::PhysicalAddress HW_MMU_Continuous::translateAddress(HW_MMU::LogicalAddress logical, Operation operation) {
    PhysicalAddress phys = logical + _base;
    if (phys < _limit) {
        return phys;
    } else { // protection error
        // schedule an event to notify that a protection error just happened
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("MMU::protection_error_interrupt_handler()");
        simulator->insertEvent(simulator->getTnow(), HW_Machine::Module_HardwareEvent(), entity);
    }
}

