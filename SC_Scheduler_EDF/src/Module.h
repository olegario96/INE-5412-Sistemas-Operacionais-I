/*
 * File:   Module.h
 * Author: cancian
 *
 * Created on September 27, 2015, 11:20 AM
 */

#ifndef MODULE_H
#define	MODULE_H

#include <list>
#include <string>
#include "Simul_Entity.h"

class Module {
public:
    Module(std::string name);
    Module(const Module& orig);
    virtual ~Module();
public:
    void run(Entity* entity);
    void addNextModule(Module* nextModule);
    void setName(std::string _name);
    std::string getName() const;
    std::list<Module*>* getNextModules() const;
protected:
    virtual void do_run(Entity* entity);
protected:
    std::string _name;
    std::list<Module*>* _nextModules;
};

#endif	/* MODULE_H */

