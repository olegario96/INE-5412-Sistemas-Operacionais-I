/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MMU.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 14:57
 */

#include "Mediator_MMU.h"
#include "HW_Machine.h"

MMU::MMU(unsigned int instance) {
    _instance = instance;
    
    //INSERT YOUR CODE HERE
    //...
    
}

MMU::MMU(const MMU& orig) {
}

MMU::~MMU() {
}

void MMU::protection_error_interrupt_handler() {
    // INSERT YOUR CODE HERE
    // ...
}

void MMU::chunk_fault_interrupt_handler() {
    // INSERT YOUR CODE HERE
    // ...
}