/*
 * File:   TimerMediator.h
 * Author: cancian
 *
 * Created on October 9, 2015, 2:55 PM
 */

#ifndef TIMERMEDIATOR_H
#define	TIMERMEDIATOR_H

//#include "ModuleInvoke_InterruptHandler.h"

class Timer {
    friend class ModuleInvoke_HardwareEvent;
    friend class ProblemTester;
public:
    Timer(unsigned int instance);

    Timer(const Timer& orig);

    virtual ~Timer();

public:
    
private:
    unsigned int _instance;
    
private:
    static void interrupt_handler();
};

#endif	/* TIMERMEDIATOR_H */

