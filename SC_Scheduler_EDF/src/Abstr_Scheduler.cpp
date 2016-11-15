/*
 * File:   Scheduler.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 11:19 AM
 */

#if 0

#include "Simul_Debug.h"
#include "Abstr_Scheduler.h"
#include "Abstr_Thread.h"
#include "Mediator_HardDisk.h"



template <typename T>
Scheduler<T>::Scheduler() {
    _readyQueue = new Scheduling_Queue<T>();
    _choosen = nullptr;
}

template <typename T>
T* Scheduler<T>::choose() {
    Debug::cout(Debug::Level::trace, "Scheduler::choose()");
    // INSERT YOUR CODE HERE
    // ...
    if (_readyQueue->empty()) {
        return nullptr;
    } else {
        T* result = _readyQueue->top();
        _choosen = result;
        //_readyQueue->pop();
        return result;
    }
}

template <typename T>
T* Scheduler<T>::choosen() {
    return _choosen;
}

template <typename T>
void Scheduler<T>::insert(T* schedulingItem) {
    this->_readyQueue->insert(schedulingItem);
}

template <typename T>
T* Scheduler<T>::remove(T* schedulingItem) {
    // remove a specific schedulingItem from the readyQueue
    this->_readyQueue->remove(schedulingItem);
}

template <typename T>
void Scheduler<T>::reschedule() {
    Debug::cout(Debug::Level::trace, "Scheduler::reschedule()");
    if (!this->_readyQueue->empty()) {
        // INSERT YOUR CODE HERE
        // ...

    }
}

#endif
