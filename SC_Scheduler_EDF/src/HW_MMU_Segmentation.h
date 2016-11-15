/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Segmentation.h
 * Author: cancian
 *
 * Created on 27 de Setembro de 2016, 20:08
 */

#ifndef HW_MMU_SEGMENTATION_H
#define HW_MMU_SEGMENTATION_H

#include "HW_MMU.h"

class HW_MMU_Segmentation : public HW_MMU {
public:

    enum ILogAddr {
        mask_LogicalSegment = 0xF0000000,  // four bits for the logical segment number. Therefore, only 16 segments are allowed
        mask_SegmentOffset  = 0x0FFFFFFF,  // at most 2^24 bits for the segment limit
        off_LogicalSegment = 28, 
        off_SegmentOffset  = 0
    };

    enum SegmentEntry {
        mask_vality = 0x80000000,
        mask_read   = 0x40000000,
        mask_write  = 0x20000000,
        mask_exec   = 0x10000000,
        mask_M      = 0x08000000,
        mask_R      = 0x04000000,
        mask_Base   = 0x00FFFFFF,  // the fields until this points stays in one entry (Information) at address (+0)
        
        mask_Limit  = 0x0FFFFFFF, // this field occupies an entity entry (Information). Therefor one segment descriptor occupies two memory addresses
        off_vality = 31,
        off_read   = 30,
        off_write  = 29,
        off_exec   = 28,
        off_M      = 27,
        off_R      = 26,
        off_Base   = 0,
        off_Limit  = 0 // in the second address (+1)
    };
public:
    HW_MMU_Segmentation();
    HW_MMU_Segmentation(const HW_MMU_Segmentation& orig);
    virtual ~HW_MMU_Segmentation();
public:
    virtual Register readRegister(unsigned int registerNum);
    virtual void writeRegister(unsigned int registerNum, Register value);
protected:
    virtual PhysicalAddress translateAddress(LogicalAddress logical, Operation operation);
private:
    PhysicalAddress _STBR; // the Segment Table Base Register (analogous to the GDT register in IA32 architecture)

};

#endif /* HW_MMU_SEGMENTATION_H */

