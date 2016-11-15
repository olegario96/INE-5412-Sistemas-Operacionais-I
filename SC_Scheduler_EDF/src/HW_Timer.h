/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_Timer.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 12:07
 */

#ifndef HW_TIMER_H
#define HW_TIMER_H

class HW_Timer {
    friend class ProblemTester;
public:
    HW_Timer();
    HW_Timer(const HW_Timer& orig);
    virtual ~HW_Timer();
    unsigned int GetStatusRegister() const;
    void SetCommandRegister(unsigned int _commandRegister);
    void SetDataRegister(unsigned int _dataRegister);
    unsigned int GetDataRegister() const;
private:
    unsigned int _dataRegister;
    unsigned int _commandRegister;
    unsigned int _statusRegister;
private:
    double _interruptPeriod;
};

#endif /* HW_TIMER_H */

