/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_DMA.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 12:07
 */

#ifndef HW_DMA_H
#define HW_DMA_H

class HW_DMA {
    friend class ProblemTester;
public:
    HW_DMA();
    HW_DMA(const HW_DMA& orig);
    virtual ~HW_DMA();
    unsigned int GetStatusRegister() const;
    void SetCommandRegister(unsigned int _commandRegister);
    void SetDataRegister(unsigned int _dataRegister);
    unsigned int GetDataRegister() const;
private:
    unsigned int _dataRegister;
    unsigned int _commandRegister;
    unsigned int _statusRegister;
};

#endif /* HW_DMA_H */

