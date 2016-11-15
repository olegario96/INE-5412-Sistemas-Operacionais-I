/*
 * File:   CPU.h
 * Author: cancian
 *
 * Created on October 10, 2015, 1:58 AM
 */

#ifndef CPU_H
#define	CPU_H

#include "Abstr_Thread.h"
#include "HW_CPU.h"

class CPU {
public:
    friend class ModuleInvoke_HardwareEvent;
    friend class ProblemTester;
public:
    typedef HW_CPU::Funct Funct;
    typedef HW_CPU::IFormat IFormat;
    typedef HW_CPU::Opcode Opcode;
    typedef HW_CPU::RegNum RegNum;
    typedef HW_CPU::Information Information;
public:
    CPU(unsigned int instance);
    CPU(const CPU& orig);
    virtual ~CPU();
public:
    static void switch_context(Thread* previous, Thread* next);
    static void restore_context(Thread* next);
    //void switch_context(Thread* previous, Thread* next);
    //void restore_context(Thread* next);
    static unsigned int getInstance();
    static void setInstance(unsigned int _instance);
    
private:
    static unsigned int _staticActualInstance;  // for SMP schedulers
    unsigned int _instance;
};

#endif	/* CPU_H */

