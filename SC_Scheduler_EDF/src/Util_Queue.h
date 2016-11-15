/*
 * File:   Queue.h
 * Author: cancian
 *
 * Created on September 27, 2015, 11:28 AM
 */

#ifndef QUEUE_H
#define	QUEUE_H

#include <list>

/**
 * Used by Thread as waiting queues for threads that uses void Thread::sleep(Queue* e) and void Thread::wakeup(Queue q)
 **/

// INSERT YOUR CODE HERE ; CHANGE THE QUEUE THE WAY YOU WANT

template <class T>
class Queue : public std::list<T> {
public: // constructors
    Queue<T>();
    Queue(const Queue& orig);
    virtual ~Queue();
    void pop();
    void insert(T* t);
    T* top();
    bool empty();
private: // user defined
    // INSERT YOUR CODE HERE
    // ...
};

template <class T>
Queue<T>::Queue() : std::list<T>() {}

template <class T>
Queue<T>::Queue(const Queue& orig) : std::list<T>(orig) {
}

template <class T> Queue<T>::~Queue() {
}


template <class T>
bool Queue<T>::empty() {
	return std::list<T>::empty();
}

template <class T>
void Queue<T>::pop() {
	std::list<T>::pop_front();
}

template <class T>
void Queue<T>::insert(T *t) {
	std::list<T>::push_back(*t);
}

template <class T>
T* Queue<T>::top() {
	return std::list<T>::top();
}


#endif	/* QUEUE_H */

