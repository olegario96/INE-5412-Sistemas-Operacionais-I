/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_DMA.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 12:07
 */

#include "HW_DMA.h"

HW_DMA::HW_DMA() {
}

HW_DMA::HW_DMA(const HW_DMA& orig) {
}

HW_DMA::~HW_DMA() {
}

unsigned int HW_DMA::GetStatusRegister() const {
    return _statusRegister;
}

void HW_DMA::SetCommandRegister(unsigned int _commandRegister) {
    this->_commandRegister = _commandRegister;
}

void HW_DMA::SetDataRegister(unsigned int _dataRegister) {
    this->_dataRegister = _dataRegister;
}

unsigned int HW_DMA::GetDataRegister() const {
    return _dataRegister;
}

