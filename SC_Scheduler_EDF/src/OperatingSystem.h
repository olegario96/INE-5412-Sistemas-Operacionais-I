/*
 * File:   System.h
 * Author: cancian
 *
 * Created on October 9, 2015, 9:04 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include "Application.h"

#include "Abstr_Scheduler.h"
#include "Abstr_MemoryManager.h"
#include "Abstr_FileSystem.h"

#include "Mediator_CPU.h"
#include "Mediator_DMA.h"
#include "Mediator_HardDisk.h"
#include "Mediator_MMU.h"
#include "Mediator_Timer.h"

#include "Traits.h"

#include "ModuleInvoke_HardwareEvent.h"

#include "Util_Queue.h"

class OperatingSystem {
private:

    OperatingSystem() {

    }

    OperatingSystem(const OperatingSystem& orig) {

    }

    virtual ~OperatingSystem() {

    }
public:

    static void ExecuteTestCode();

    static Scheduler<Thread>* Process_Scheduler() {
        static Scheduler<Thread>* _processScheduler = new Scheduler<Thread>();
        return _processScheduler;
    }

    static FileSystem* File_System() {
        static FileSystem* _fileSystem = new FileSystem();
        return _fileSystem;
    }

    static Scheduler<DiskAccessRequest>* Disk_Scheduler() {
        static Scheduler<DiskAccessRequest>* _diskScheduler = new Scheduler<DiskAccessRequest>();
        return _diskScheduler;
    }

    static MemoryManager* Memory_Manager() {
        static MemoryManager* _memoryManager = new MemoryManager();
        return _memoryManager;
    }

    static Timer* Timer_Mediator() {
        static Timer* _timer = new Timer(0);
        return _timer;
    }

    static DMA* DMA_Mediator() {
        static DMA* _dma = new DMA(0);
        return _dma;
    }

    static CPU* CPU_Mediator() {
        static CPU* _cpu = new CPU(0);
        return _cpu;
    }

    static MMU* MMU_Mediator() {
        static MMU* _mmu = new MMU(0);
        return _mmu;
    }

    static HardDisk* HardDisk_Mediator() {
        static HardDisk* _harddisk = new HardDisk(0);
        return _harddisk;
    }

    static void SetBootApplication(Application* app);
    static void LoadApplication(Application* app, MMU::PhysicalAddress address);
    static void Init();

private:
    static HW_MMU::Information asmm(std::string mnemonic);

};

#endif	/* SYSTEM_H */

