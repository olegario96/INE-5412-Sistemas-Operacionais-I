/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_RAM.h
 * Author: cancian
 *
 * Created on September 13, 2016, 1:56 PM
 */

#ifndef HW_RAM_H
#define HW_RAM_H

#include "HW_MMU.h"
#include "Traits.h"

class HW_RAM {
    friend class ProblemTester;
public:
    typedef HW_MMU::PhysicalAddress PhysicalAddress;
    typedef HW_MMU::Information Information;
public:
    HW_RAM();
    HW_RAM(const HW_RAM& orig);
    virtual ~HW_RAM();
public:
    Information read(PhysicalAddress address);
    void write(PhysicalAddress address, Information data);
private:
    Information _ramMemory[Traits<HW_MMU>::RAMsize];
};

#endif /* HW_RAM_H */

