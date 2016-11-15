/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_Machine.h
 * Author: cancian
 *
 * Created on September 13, 2016, 4:04 PM
 */

#ifndef HW_MACHINE_H
#define HW_MACHINE_H

#include "HW_CPU.h"
#include "HW_DMA.h"
#include "HW_HardDisk.h"
#include "HW_MMU.h"
#include "HW_MMU_Continuous.h"
#include "HW_MMU_Paging.h"
#include "HW_RAM.h"
#include "HW_Timer.h"

#include "ModuleInvoke_HardwareEvent.h"

#include "Application.h"
#include "HW_MMU_Segmentation.h"

class HW_Machine {
private:
    HW_Machine();
    HW_Machine(const HW_Machine& orig);
    virtual ~HW_Machine();
public:

    static HW_CPU* CPU() {
        static HW_CPU* _cpu = new HW_CPU();
        return _cpu;
    }

    static HW_RAM* RAM() {
        static HW_RAM* _ram = new HW_RAM();
        return _ram;
    }

    static HW_HardDisk* HardDisk() {
        static HW_HardDisk* _hardDisk = new HW_HardDisk();
        return _hardDisk;
    }

    static HW_Timer* Timer() {
        static HW_Timer* _timer = new HW_Timer();
        return _timer;
    }

    static HW_DMA* DMA() {
        static HW_DMA* _dma = new HW_DMA();
        return _dma;
    }

    static HW_MMU* MMU() {
        static HW_MMU* _mmu;
        if (_mmu == nullptr) {
            Traits<Model>::ProblemSolving problem = Traits<Model>::problemChoosen;
            if ((problem == Traits<Model>::BestFit111) || (problem == Traits<Model>::WorstFit112)) {
                _mmu = new HW_MMU_Continuous(); // mmu for continuous memory (dynamic partitions)
            } else if ((problem == Traits<Model>::LFU122) || (problem == Traits<Model>::LRU121) || (problem == Traits<Model>::NRU123)) {
                _mmu = new HW_MMU_Paging(); // mmu for paging
            } else if (problem == Traits<Model>::Segment13) {
                _mmu = new HW_MMU_Segmentation(); // mmu for segmentation
            } else {
                _mmu = new HW_MMU(); // just a dummy MMU
            }
        }
        return _mmu;
    }

    static ModuleInvoke_HardwareEvent* Module_HardwareEvent() { // for simulation purposes. Allow simulation to invoke a class method associated to hardware events, mainly interrupts
        static ModuleInvoke_HardwareEvent* _moduleHardwareEvent;
        if (_moduleHardwareEvent == nullptr) {

            _moduleHardwareEvent = new ModuleInvoke_HardwareEvent("HardwareEvent");
        }
        return _moduleHardwareEvent;
    }

    static void Init() {
        RAM();
        MMU();
        DMA();
        HardDisk();
        Timer();
        CPU();
    }

private:

};

#endif /* HW_MACHINE_H */

