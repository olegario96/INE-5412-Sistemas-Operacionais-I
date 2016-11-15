/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alarm.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 14:42
 */

#ifndef ALARM_H
#define ALARM_H

class Alarm {
    friend class ProblemTester;
public:
    typedef double Microsecond;
public:
    Alarm();
    Alarm(const Alarm& orig);
    virtual ~Alarm();
    Microsecond getTimer();
public:
    static void delay(const Microsecond & time);  
private:
    static void init();
    Microsecond timer;
};

#endif /* ALARM_H */

