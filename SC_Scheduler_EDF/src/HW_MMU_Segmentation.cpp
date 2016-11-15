/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Segmentation.cpp
 * Author: cancian
 * 
 * Created on 27 de Setembro de 2016, 20:08
 */

#include "HW_MMU_Segmentation.h"
#include "HW_Machine.h"

#include "Simulator.h"

#include "Traits.h"

HW_MMU_Segmentation::HW_MMU_Segmentation() {
    // INSERT YOUR CODE HERE
    // ...
    
    // It will create basic Segment Table at top of RAM defining one big segment for the entire RAM
    // This code should be somewhere else (when loading an Application), but it is here for convenience
    Information addr = Traits<HW_MMU>::RAMsize-2; // base of Segmentation Table
    this->_STBR = addr;  // by default, STBR points to the new Segmentation Table
    // fill the segmentation table with one segment descriptor (two entries -- two addresses)
    Information data =  (1 << HW_MMU_Segmentation::off_read) + // segment can be read
                        (1 << HW_MMU_Segmentation::off_write) + // segment can be write
                        (1 << HW_MMU_Segmentation::off_vality) + // segment is in memory
                        (0x000000 << HW_MMU_Segmentation::off_Base); // segment starts at base address 0
    HW_Machine::RAM()->write(addr, data);
    data = (Traits<HW_MMU>::RAMsize << HW_MMU_Segmentation::off_Limit); // segment as the size of the entire RAM 
    HW_Machine::RAM()->write(++addr, data);
    // segment table loaded in memory!
 }

HW_MMU_Segmentation::HW_MMU_Segmentation(const HW_MMU_Segmentation& orig) {
}

HW_MMU_Segmentation::~HW_MMU_Segmentation() {
}

/*
 *
 */
HW_MMU_Segmentation::Register HW_MMU_Segmentation::readRegister(unsigned int registerNum) {
    if (registerNum == 0) {
        return this->_STBR;
    }
    return 0;
}

/*
 *
 */
void HW_MMU_Segmentation::writeRegister(unsigned int registerNum, HW_MMU_Segmentation::Register value) {
    if (registerNum == 0) {
        this->_STBR = value;
    }
}

/*
 *
 */
HW_MMU_Segmentation::PhysicalAddress HW_MMU_Segmentation::translateAddress(HW_MMU_Segmentation::LogicalAddress logical, HW_MMU_Segmentation::Operation operation) {
    unsigned int logicalSegmentNumber = (logical & HW_MMU_Segmentation::mask_LogicalSegment) >> HW_MMU_Segmentation::off_LogicalSegment;
    unsigned int logicalSegmentOffset = (logical & HW_MMU_Segmentation::mask_SegmentOffset) >> HW_MMU_Segmentation::off_SegmentOffset; 
    PhysicalAddress segmentEntryAddress = this->_STBR + logicalSegmentNumber * 2; // each segment descriptor takes two addresses in the RAM memory
    Information segmentEntry1 = HW_Machine::RAM()->read(segmentEntryAddress);
    Information segmentEntry2 = HW_Machine::RAM()->read(segmentEntryAddress+1); //this entry (half of the descriptor) has only the offset

    unsigned int segmentBase = (segmentEntry1 & HW_MMU_Segmentation::mask_Base) >> HW_MMU_Segmentation::off_Base;    
    unsigned int segmentSize = (segmentEntry2 & HW_MMU_Segmentation::mask_Limit) >> HW_MMU_Segmentation::off_Limit;    
    bool isSegmentInMemory = (segmentEntry1 & HW_MMU_Segmentation::mask_vality) > 0;
    bool hasProtectionError = (!(segmentEntry1 & HW_MMU_Segmentation::mask_read) && (operation==Operation::Read) );
    hasProtectionError |= (!(segmentEntry1 & HW_MMU_Segmentation::mask_write) && (operation==Operation::Write) );
    hasProtectionError |= (logicalSegmentOffset > segmentSize);
    
    if (hasProtectionError) {
        // schedule an event to notify that a protection error just happened
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("MMU::protection_error_interrupt_handler()");
        simulator->insertEvent(simulator->getTnow(), HW_Machine::Module_HardwareEvent(), entity);
    } else if (isSegmentInMemory) {
        PhysicalAddress phys = segmentBase + logicalSegmentOffset;
        return phys;
    } else { // segment fault
        // schedule an event to notify that a protection error just happened
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("MMU::chunk_fault_interrupt_handler()");
        simulator->insertEvent(simulator->getTnow(), HW_Machine::Module_HardwareEvent(), entity);
    }
}