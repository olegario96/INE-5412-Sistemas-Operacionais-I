/*
 * File:   Process.h
 * Author: cancian
 *
 * Created on August 31, 2015, 7:49 AM
 */

#ifndef PROCESS_H
#define	PROCESS_H

#include <list>
#include <queue>

#include "Abstr_MemoryManager.h"
#include "Abstr_MemoryChunk.h"
#include "Simul_Entity.h"
//#include "ModuleInvoke_ProcessExec.h"

class Process {
    friend class Thread;
    //friend class ModuleInvoke_ProcessExec; // for simulation purposes only
    friend class ProblemTester; // for simulation purposes only
    friend class Simulator;
    
    // scructs for grouping process' attributes

    struct IdentificationInformation {
        unsigned int _processId;
        unsigned int _parentId;
        int _priority;
        // ...
    };

    struct AccountInformation {
        double _CPUTime;
        double _waitingTime;
        double _dispatchedTime;
        double _blockedTime;
        // ...
    };

    struct ChunkTable {
        //MemoryChunk* _chunk;
        std::list<MemoryChunk*>* _chunks;
    };


public: // constrs
    Process(unsigned int parentId);
    Process(const Process& orig);
    virtual ~Process();
public: // id info
    unsigned int getParentId() const;
    unsigned int getId() const;
    Entity* getEntity() const;
public: // statics

    static unsigned int getNewId() {
        static unsigned int _lastId = 0;
        return ++_lastId;
    }

    static std::list<Process*>* getProcessesList() { // return the listr of all processes in the system
        static std::list<Process*>* _ProcessesList;
        if (_ProcessesList == nullptr) {
            _ProcessesList = new std::list<Process*>();
        }
        return _ProcessesList;
    }

    static Process* exec(); // execute a new process
    static void exit(int status = 0); // finishes the running process
private:
    IdentificationInformation _idInfo;
    ChunkTable _memInfo;
    AccountInformation _cpuTime;
public: // For simulation use only. Do not change

    Entity* getEntity() {
        return _entity;
    }

private: // for simulator use only. Do not change
    Entity* _entity; //used only by the simulator
public: // USER DEFINED
    // INSERT YOUR CODE HERE
    AccountInformation getCpuTime() {
        return _cpuTime;
    }

private: // USER DEFINED
    // INSERT YOUR CODE HERE
};

#endif	/* PROCESS_H */
