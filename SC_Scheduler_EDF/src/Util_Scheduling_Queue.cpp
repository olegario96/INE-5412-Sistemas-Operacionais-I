/*
 * File:   Scheduling_Queue.cpp
 * Author: cancian
 *
 * Created on October 9, 2015, 9:34 PM
 */

#if 0

#include "Util_Scheduling_Queue.h"

template <typename T>
Scheduling_Queue<T>::Scheduling_Queue() {
    // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
    
    //_queue = new std::priority_queue<T*>();
    _queue = new std::list<T*>();
}

template <typename T>
Scheduling_Queue<T>::Scheduling_Queue(const Scheduling_Queue& orig) {
}

template <typename T>
Scheduling_Queue<T>::~Scheduling_Queue() {
}

template <typename T>
bool Scheduling_Queue<T>::empty() {
    // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
    return _queue->empty();
}

template <typename T>
void Scheduling_Queue<T>::pop() {
    // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
    if (!_queue->empty()) {
        _queue->erase(_queue->begin());
    }
}

template <typename T>
void Scheduling_Queue<T>::remove(T* t) {
    _queue->remove(t);
}

template <typename T>
T* Scheduling_Queue<T>::top() {
    // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
    return (*_queue->begin());
}

template <typename T>
void Scheduling_Queue<T>::insert(T* t) {
    // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
    _queue->insert(_queue->begin(), t);
    _queue->sort([] (const T* a, const T * b) {
        return true;////////////////////////a->getPriority() <= b->getPriority();
    });
}

template <typename T>
void Scheduling_Queue<T>::sort() {
    _queue->sort([] (const T* a, const T * b) {
        return true;////////////////////////a->getPriority() <= b->getPriority();
    });
}

#endif