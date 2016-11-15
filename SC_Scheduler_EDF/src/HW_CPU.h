/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_CPU.h
 * Author: cancian
 *
 * Created on 31 de Agosto de 2016, 14:12
 */

#ifndef HW_CPU_H
#define HW_CPU_H

#include "HW_MMU.h"

class HW_CPU {
    friend class ProblemTester;
public:
    typedef HW_MMU::Information Information;
    typedef HW_MMU::Register Register;

    enum RegNum {
        zero=0, at=1, v0=2,v1=3, a0=4, a1=5, a2=6, a3=7, 
        t0=7, t1=8, t2=9, t3=10, t4=11, t5=12, t6=13, t7=14, 
        s0=16, s1=17, s2=18, s3=19, s4=20, s5=21, s6=22, s7=23, 
        t8=24, t9=25, 
        k0=26, k1=27, gp=28, sp=29, fp=30, ra=31, pc=32 //pc must be always the last
    };
    
    enum Opcode {
        RType = 0x00,
        addi  = 0x08,
        andi  = 0x0c,
        ori   = 0x0d,
        lui   = 0x0f,
        slti  = 0x0a,
        beq   = 0x04,
        bne   = 0x05,
        j     = 0x02,
        jal   = 0x03,
        lw    = 0x23,
        sw    = 0x2b
    };
    
    enum Funct {
        add   = 0x20,
        andd  = 0x24,
        orr   = 0x25,
        sub   = 0x22,        
        slt   = 0x2a,
        jr    = 0x08,
        nop   = 0x00,
        syscall = 0x0c        
    };
    
    enum IFormat {
        off_opcode = 26,
        off_rs = 21,
        off_rd = 11,
        off_rt = 16,
        off_shamt = 6,
        off_funct = 0,
        off_const = 0,
        off_addr = 0
    };

public:
    HW_CPU();
    HW_CPU(const HW_CPU& orig);
    virtual ~HW_CPU();
public:
    Register readRegister(RegNum registerNum);
    void writeRegister(RegNum registerNum, Register value);
    void pulse();
private:
    Register _registers[RegNum::pc + 1]; // this is why pc must be the last
    bool _kernelMode;
};

#endif /* HW_CPU_H */

