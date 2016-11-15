/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Continuous.h
 * Author: cancian
 *
 * Created on 23 de Setembro de 2016, 16:25
 */

#ifndef HW_MMU_CONTINUOUS_H
#define HW_MMU_CONTINUOUS_H

#include "HW_MMU.h"

class HW_MMU_Continuous : public HW_MMU {
public:
    HW_MMU_Continuous();
    HW_MMU_Continuous(const HW_MMU_Continuous& orig);
    virtual ~HW_MMU_Continuous();
public:
    virtual Register readRegister(unsigned int registerNum);
    virtual void writeRegister(unsigned int registerNum, Register value);
protected:
    virtual PhysicalAddress translateAddress(LogicalAddress logical, Operation operation);
private:
    PhysicalAddress _base;
    PhysicalAddress _limit;
};

#endif /* HW_MMU_CONTINUOUS_H */

