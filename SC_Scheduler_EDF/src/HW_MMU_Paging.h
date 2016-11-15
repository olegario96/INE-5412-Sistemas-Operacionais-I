/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Paging.h
 * Author: cancian
 *
 * Created on 23 de Setembro de 2016, 16:49
 */

#ifndef HW_MMU_PAGING_H
#define HW_MMU_PAGING_H

#include "HW_MMU.h"

class HW_MMU_Paging : public HW_MMU {
public:

    enum ILogAddr {
        mask_LogicalPage = 0xFFFFF000,
        mask_PageOffset  = 0x00000FFF,
        off_LogicalPage  = 12,
        off_PageOffset   = 0
    };

    enum PageEntry {
        mask_vality = 0x80000000,
        mask_read   = 0x40000000,
        mask_write  = 0x20000000,
        mask_exec   = 0x10000000,
        mask_M      = 0x08000000,
        mask_R      = 0x04000000,
        mask_Frame  = 0x00FFFFFF,
        off_vality  = 31,
        off_read    = 30,
        off_write   = 29,
        off_exec    = 28,
        off_M       = 27,
        off_R       = 26,
        off_Frame   = 0
    };

public:
    HW_MMU_Paging();
    HW_MMU_Paging(const HW_MMU_Paging& orig);
    virtual ~HW_MMU_Paging();
public:
    virtual Register readRegister(unsigned int registerNum);
    virtual void writeRegister(unsigned int registerNum, Register value);
protected:
    virtual PhysicalAddress translateAddress(LogicalAddress logical, Operation operation);
private:
    PhysicalAddress _PTBR; // Page Table Base Register
};

#endif /* HW_MMU_PAGING_H */

