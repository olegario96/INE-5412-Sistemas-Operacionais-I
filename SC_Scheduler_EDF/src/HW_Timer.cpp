/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_Timer.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 12:07
 */

#include "HW_Timer.h"
#include "Simulator.h"

#include "Traits.h"
#include "OperatingSystem.h"

HW_Timer::HW_Timer() {
    _interruptPeriod = Traits<HW_Timer>::timer_interrupt_period;
}

HW_Timer::HW_Timer(const HW_Timer& orig) {
}

HW_Timer::~HW_Timer() {
}

unsigned int HW_Timer::GetStatusRegister() const {
    return _statusRegister;
}

void HW_Timer::SetCommandRegister(unsigned int _commandRegister) {
    this->_commandRegister = _commandRegister;
}

void HW_Timer::SetDataRegister(unsigned int _dataRegister) {
    this->_dataRegister = _dataRegister;
}

unsigned int HW_Timer::GetDataRegister() const {
    return _dataRegister;
}

