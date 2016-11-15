/*
 * File:   Event.h
 * Author: cancian
 *
 * Created on September 27, 2015, 11:43 AM
 */

#ifndef EVENT_H
#define	EVENT_H

#include "Module.h"
#include "Simul_Entity.h"

class Event {
public:
    Event(double time, Module* module, Entity* entity);
    Event(const Event& orig);
    virtual ~Event();
public:
    Entity* getEntity() const;
    Module* getModule() const;
    double getTime() const;
private:
    double _time;
    Module* _module;
    Entity* _entity;
};

#endif	/* EVENT_H */

