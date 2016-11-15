/*
 * File:   Scheduling_Queue.h
 * Author: cacian
 *
 * Created on October 9, 2015, 9:34 PM
 */

#ifndef SCHEDULING_QUEUE_H
#define SCHEDULING_QUEUE_H

#include <queue>
#include <list>

template <typename T>
class Scheduling_Queue /* insert hierarchy if you want */ {
public:

    Scheduling_Queue() {
        // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE

        //_queue = new std::priority_queue<T*>();
        _queue = new std::list<T*>();
    }

    Scheduling_Queue(const Scheduling_Queue& orig) {
    }

    virtual ~Scheduling_Queue() {
    }
public:

    bool empty() {
        // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
        return _queue->empty();
    }

    void insert(T* t) {
        // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
        _queue->insert(_queue->begin(), t);

        //sort()
        _queue->sort([] (const T* a, const T * b) {
            return a->getPriority() <= b->getPriority();
        });
    }

    void remove(T* t) {
        _queue->remove(t);
    }

    void pop() { // remove the top (head) element
        // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
        if (!_queue->empty()) {
            _queue->erase(_queue->begin());
        }
    }

    T* top() { // returns the top (head) element

        // CHANGE AS NECESSARY IF YOU CHOOSE ANOTHER QUEUE
        return (*_queue->begin());
    }

    void sort() {
        _queue->sort([] (const T* a, const T * b) {
            return a->getPriority() <= b->getPriority();
        });
    }

private:
    // INSERT YOUR CODE HERE
        // ...

    //std::priority_queue<T*>* _queue;
    std::list<T*>* _queue;
};

#endif /* SCHEDULING_QUEUE_H */
