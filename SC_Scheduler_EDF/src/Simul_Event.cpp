/*
 * File:   Event.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 11:43 AM
 */

#include "Simul_Event.h"

Event::Event(double time, Module* module, Entity* entity) {
    this->_time = time;
    this->_module = module;
    this->_entity = entity;
}

Event::Event(const Event& orig) {
}

Entity* Event::getEntity() const {
    return _entity;
}

Module* Event::getModule() const {
    return _module;
}

double Event::getTime() const {
    return _time;
}

Event::~Event() {
}

