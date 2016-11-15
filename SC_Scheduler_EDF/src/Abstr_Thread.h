/*
 * File:   Thread.h
 * Author: cancian
 *
 * Created on September 27, 2015, 10:30 AM
 */

#ifndef THREAD_H
#define THREAD_H

#include <list>

#include "Util_Queue.h"
#include "Abstr_Process.h"
#include "Mediator_Timer.h"
//#include "ModuleInvoke_ThreadExec.h"

#define DEAD_LINE 30 // realizar entrada de deadline

class Thread {
    //friend class ModuleInvoke_ThreadExec; // simulator use only
    friend class Timer;
    friend class Process;
    friend class OperatingSystem;
    friend class ProblemTester; // for simulation purposes only

    enum State {
        RUNNING,
        READY,
        WAITING,
        FINISHING
    };

    enum Criterion {
        HIGH,
        NORMAL,
        LOW,
        MAIN,
        IDLE
    };

    /**
     *  struct for grouping threads' attributes
     **/
    struct AccountInformation {
        // do not change
        int _priority; // this attribute MUST BE the one used to sort the Schelung_Queue, no matter the scheduler algorithm
        double _arrivalTime;
        double _cpuBurstTime;
        double _cpuTime;
        double _waitingTime;
        double _blockedTime;
        // add here another information you need
        // INSERT YOUR CODE HERE
        // ...
        double _deadLineTime;
        double _dispatchedTime;
        double _cpuAux;
        double _waitAux;
        double _blockedAux;
    };

public: // constructors
    Thread(Process* task, Thread::State state = Thread::State::READY);
    Thread(const Thread& orig);
    virtual ~Thread();
public: // statics
    static void sleep(Queue<Thread*> * q);
    static void wakeup(Queue<Thread*> * q);
    static Thread* thread_create(Process* parent);

    static std::list<Thread*>* getThreadsList() {
        static std::list<Thread*>* _threadsList;
        if (_threadsList == nullptr) {
            _threadsList = new std::list<Thread*>();
        }
        return _threadsList;
    }
protected: // statics
    static Thread* _running;
    static void yield();
    static void exit(int status = 0);
    static Thread* running();
    static void dispatch(Thread* previous, Thread* next);

    static unsigned int getNewId() {
        static unsigned int _lastId = 0;
        return ++_lastId;
    }
public: //
    int join();
    Process* getProcess();
    int getPriority() const;
    std::list<Thread*>* getQueue() {
        return _queue;
    }
    int getDeadLineTime();
    unsigned int getId() {
        return _id;
    }
    State getState() {
        return _state;
    }
protected:
    Process * _process;
    State _state;
    unsigned int _id;
    AccountInformation _accountInfo;

public: // USER DEFINED
    // INSERT YOUR CODE HERE
    // ...
private: // USER DEFINED
    // INSERT YOUR CODE HERE
    // ...
    //Queue<Thread*>* _queue;
    std::list<Thread*>* _queue;
};

#endif  /* THREAD_H */
