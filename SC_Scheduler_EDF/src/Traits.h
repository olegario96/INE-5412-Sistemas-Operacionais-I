/*
 * File:   Traits.h
 * Author: cancian
 *
 * Created on September 27, 2015, 4:16 PM
 */


/*
 * File:   Traits.h
 * Author: cancian
 *
 * Created on September 27, 2015, 4:16 PM
 */

#ifndef TRAITS_H
#define	TRAITS_H

#include "Simul_Debug.h"
#include "Model.h"

#include "Abstr_Thread.h"
#include "Abstr_Scheduler.h"
#include "Abstr_Process.h"

#include "Mediator_CPU.h"
#include "Mediator_Timer.h"

#include "HW_HardDisk.h"
#include "HW_MMU.h"
#include "HW_Timer.h"

template<typename T>
struct Traits {
    static const bool enabled = true;
    static const bool debugged = true;
};

/*
 *  SIMULATION AND PROBLEM BEING SOLVED
 */

template<> struct Traits<Model> {
    enum ProblemType { MemoryManagement, ProcessScheduling, ProcessManagement, Deadlock, DiskScheduling, FileSystem, DevicesAndTime };
    enum ProblemSolving{   
        // MemoryMAnagement
        BestFit111, WorstFit112, LRU121, LFU122, NRU123, Segment13, 
        // Process Scheduling
        Priority141, Fair142, SRTF143, Multiple144, Linux145, EDF151, RM152, Sporadic153,
        // process management
        ProcessManagement115,
        // Deadlock
        Deadlock17, Banker18,
        // DisckScheduling
        SSTF191, Scan192, CScan193,
        // FileSystem
        Linked101, Indexed1102, Multilevel1103, Bitmap1111, Grouping1112,
        // DevicesAnsTime
        Alarm12, I2C1141, SPI1142 };
    static const ProblemType   problemType = ProcessScheduling; // SET HERE THE COMPUTACIONAL TYPE YOU ARE SOLVING (THE ONE YOU HAVE CHOOSEN AS TOUR "SC")
    static const ProblemSolving problemChoosen = EDF151; // SET HERE THE COMPUTACIONAL SYSTEM YOU ARE SOLVING (THE ONE YOU HAVE CHOOSEN AS TOUR "SC")
    static constexpr double simulationLength = 500.0; // time units
    static constexpr double firstCreation = 0.0;       // time units
};

/*
 *  DEBUG
 */

template<> struct Traits<Debug> { // CHANGE THE DEBUG LEVEL HERE SETTING THE LEVELS YOU WANT TO SHOW
    // debug levels
    static const bool error = true;
    static const bool warning = true;        // warning shows execution major warnings
    static const bool trace = true; //false; // trace shows methods invoked (in terms of operating systems, not simulation)
    static const bool info = true; //true;   // info shows major information produced inside methods (in terms of operating systems, not simulation)
    static const bool fine = false; //true;   // fine shows minor information produced inside methods (in terms of simulation, just like entity has arrive to or is leaving a module)
    //
    static const bool showEntityAttributes = true;
    static const bool showListOfEvents = true;
    static const bool pauseOnEveryEvent = false; //true;
};


/*
 *  ABSTRACTIONS 
 */


template<> struct Traits<Process> {
    static constexpr double timeBetweenCreations = 5e4; // time units
    static constexpr unsigned int minAddressSpace = 100e3; // bytes
    static constexpr unsigned int maxAddressSpace = 100e3; // bytes
};


template<> struct Traits<Thread> {
    static constexpr double minCpuBurst = 50.0;   // time units
    static constexpr double maxCpuBurst = 50.0;   // time units
    static constexpr int maxBursts = 1;            // CPUBurst
    static constexpr int minThreadsPerProcess = 1; // threads
    static constexpr int maxThreadsPerProcess = 1; // threads
};

template<> struct Traits<MemoryManager> {
    enum AllocationAlgorithm {FirstFit, NextFit, BestFit, WorstFit};
    enum ReplacementAlgorithm {FIFO, LRU, LFU, NFU, SecondChance};
    static constexpr unsigned int physicalMemorySize = 1e6; // bytes
    static constexpr AllocationAlgorithm allocationAlgorithm = AllocationAlgorithm::BestFit;
    static constexpr ReplacementAlgorithm replacementAlgorithm = ReplacementAlgorithm::FIFO;
};

template<> struct Traits<Scheduler<Thread>> {
    static constexpr double timeSlice = 200.0; // time units
};


/*
 *  MEDIATORS
 */

template<> struct Traits<CPU> {
    static constexpr double context_switch_overhead = 1.0; // time units
};

/*
 *  HARDWARE 
 */



template<> struct Traits<HW_Timer> {
    static constexpr double timer_interrupt_period = 20; // time units
};

template<> struct Traits<HW_MMU> {
    static constexpr unsigned int RAMsize = 1024; // information units (eg: bytes) in the physical RAM. RAM width is "Information" (an unsigned int)
};

template<> struct Traits<HW_HardDisk> {
    static constexpr unsigned int diskSectorSize = 64; 
    static constexpr unsigned int numSurfaces = 1;
    static constexpr unsigned int numTracksPerSurface = 1000;
    static constexpr unsigned int numSectorsPerTrack = 2;
    static constexpr double sectorMovementTime = 10;  // time units to move head from one sector to another adjacent one
};


#endif	/* TRAITS_H */
