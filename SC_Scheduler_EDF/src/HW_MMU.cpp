/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 11:55
 */

#include "HW_MMU.h"
#include "HW_Machine.h"

HW_MMU::HW_MMU() {
    // INSERT YOUR CODE HERE
    // ...
    
}

HW_MMU::HW_MMU(const HW_MMU& orig) {
}

HW_MMU::~HW_MMU() {
}

HW_MMU::PhysicalAddress HW_MMU::translateAddress(LogicalAddress logical, Operation operation){
    PhysicalAddress physical;
    // Translate logical into physical address
    // INSERT YOUR CODE HERE
    // ...
    physical = logical; // immediate address translation  
    
    return physical;
}

 HW_MMU::Register HW_MMU::readRegister(unsigned int registerNum) {
     
 }
 void HW_MMU::writeRegister(unsigned int registerNum, HW_MMU::Register value) {
     
 }


HW_MMU::Information HW_MMU::readMemory(HW_MMU::LogicalAddress address) {
    PhysicalAddress phys = translateAddress(address, Operation::Read);
    return HW_Machine::RAM()->read(phys);
}

void HW_MMU::writeMemory(HW_MMU::LogicalAddress address, HW_MMU::Information data) {
    PhysicalAddress phys = translateAddress(address, Operation::Write);
    HW_Machine::RAM()->write(phys, data);
}
