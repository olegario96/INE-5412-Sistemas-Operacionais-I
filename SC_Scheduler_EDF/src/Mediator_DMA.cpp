/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DMA.cpp
 * Author: cancian
 * 
 * Created on September 20, 2016, 3:16 PM
 */

#include "Mediator_DMA.h"

DMA::DMA(unsigned int instance) {
    _instance = instance;
}

DMA::DMA(const DMA& orig) {
}

DMA::~DMA() {
}

void DMA::interrupt_handler() { //static
}