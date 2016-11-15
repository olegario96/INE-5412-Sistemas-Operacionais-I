/*
 * File:   Tester.h
 * Author: cancian
 *
 * Created on November 7, 2015, 3:44 PM
 */

#ifndef TESTER_H
#define	TESTER_H

#include <iostream>

#include "Abstr_Process.h"
#include "Abstr_Thread.h"
#include "ModelBuilder.h"
#include "Simulator.h"

class TestInfo {
public:
    TestInfo() {
        _failed = true;
        _testName = "none";
        _message = "Test has failed because it was not implemented yet";
    }

    void SetFailed(bool _failed) {
        this->_failed = _failed;
    }

    bool IsFailed() const {
        return _failed;
    }

    void SetMessage(std::string _message) {
        this->_message = _message;
    }

    std::string GetMessage() const {
        return _message;
    }

    void SetTestName(std::string _testName) {
        this->_testName = _testName;
    }

    std::string GetTestName() const {
        return _testName;
    }
private:
    std::string _testName;
    std::string _message;
    bool _failed;
};

class ProblemTester {
public:
    ProblemTester();
    ProblemTester(const ProblemTester& orig);
    virtual ~ProblemTester();
    void test(int numTest); //virtual 
    void setBuilder(ModelBuilder* modelBuilder) {_modelBuilder = modelBuilder;}
protected:
    virtual TestInfo do_real_test(int numTest);
    ModelBuilder* _modelBuilder;
private:
    void _clearSystem();
//protected: // provide access of private attributes from friends to subclasses of Tester
//    Process * _thread_process(Thread* thread) {return thread->_process;}
//    Thread::AccountInformation  _thread_accountInfo(Thread* thread) {return thread->_accountInfo;}
//    std::list<Thread*>* _thread_queue(Thread* thread) {return thread->_queue;}
//    Thread* _Thread_running() {return Thread::_running;}
//    void _Thread_running(Thread* thread) {Thread::_running = thread;}
//    void _thread_yield(Thread* thread){thread->yield();}
//    Thread::State _thread_state(Thread* thread) {return thread->_state;}
//    void _thread_state(Thread* thread, Thread::State state) {thread->_state = state;}
//    void _thread_exit(Thread* thread) {thread->exit();}
//    typedef Thread::State Thread_State;
//    void _simulator_tnow(Simulator *simulator, double tnow) {simulator->_tnow = tnow;}
//    void _TimerMediator_interrupt_handler() {Timer::interrupt_handler();}
};

#endif	/* TESTER_H */

