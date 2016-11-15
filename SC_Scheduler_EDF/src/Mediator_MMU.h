/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MMU.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 14:57
 */

#ifndef MMU_H
#define MMU_H

#include "HW_MMU.h"


class MMU {
    friend class ModuleInvoke_HardwareEvent;
    friend class ProblemTester;    
public:
    typedef HW_MMU::PhysicalAddress PhysicalAddress; 
public:
    MMU(unsigned int instance);
    MMU(const MMU& orig);
    virtual ~MMU();
public:
    // INSERT YOUR CODE HERE
    // (Methods to set MMU registers)
    // ...
private:
    unsigned int _instance;
    
private:
    static void protection_error_interrupt_handler();
    static void chunk_fault_interrupt_handler();
};

#endif /* MMU_H */

