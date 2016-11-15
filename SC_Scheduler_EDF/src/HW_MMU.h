/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 11:55
 */

#ifndef HW_MMU_H
#define HW_MMU_H

class HW_MMU {
    friend class ProblemTester;
public:
    typedef unsigned int PhysicalAddress;
    typedef unsigned long LogicalAddress;
    typedef unsigned int Information; // 32 bits, just like MIPS/DLX (memory is 32 bits wide. PC=PC+1, instead)
    typedef unsigned int Register;
    
    enum Operation {Read, Write};
public:
    HW_MMU();
    HW_MMU(const HW_MMU& orig);
    virtual ~HW_MMU();
public:
    Information readMemory(LogicalAddress address);
    void writeMemory(LogicalAddress address, Information data);
    virtual Register readRegister(unsigned int registerNum);
    virtual void writeRegister(unsigned int registerNum, Register value);
protected:
    virtual PhysicalAddress translateAddress(LogicalAddress logical, Operation operation);

};

#endif /* HW_MMU_H */

