/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DMA.h
 * Author: cancian
 *
 * Created on September 20, 2016, 3:16 PM
 */

#ifndef DMA_H
#define DMA_H

class DMA {
public:
    friend class ModuleInvoke_HardwareEvent;
    friend class ProblemTester;
public:
    DMA(unsigned int instance);
    DMA(const DMA& orig);
    virtual ~DMA();
public:
    // INSERT YOUR CODE HERE
    // (methods to program the DMA to perform a block transfer)
    // ...
private:
    unsigned int _instance;
private:
    static void interrupt_handler();

};

#endif /* DMA_H */

