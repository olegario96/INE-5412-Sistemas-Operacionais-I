/*
 * File:   CPU.cpp
 * Author: cancian
 *
 * Created on October 10, 2015, 1:58 AM
 */

#include <assert.h>



#include "Mediator_CPU.h"
#include "Simulator.h"
#include "Module.h"
#include "Simul_Entity.h"
#include "Traits.h"

unsigned int CPU::_staticActualInstance = 0; 

CPU::CPU(unsigned int instance) {
    _staticActualInstance = instance;
    _instance = instance;
}

CPU::CPU(const CPU& orig) {
}

CPU::~CPU() {
}

void CPU::switch_context(Thread* previous, Thread* next) {
    Debug::cout(Debug::Level::trace, "CPU[" + std::to_string(_staticActualInstance) + "]::swith_context(" + std::to_string(reinterpret_cast<unsigned long> (previous)) + "," + std::to_string(reinterpret_cast<unsigned long> (next)) + ") "); //will happen at time [" + std::to_string(time) + "]");

    Simulator* simulator = Simulator::getInstance();
    double time = simulator->getTnow();
    time += Traits<CPU>::context_switch_overhead;
    Module* module = simulator->getModel()->getModule("InvokeThreadExec"); // must match name given on main
    std::string strPrevious = std::to_string(reinterpret_cast<unsigned long> (previous));
    std::string strNext = std::to_string(reinterpret_cast<unsigned long> (next));
    std::string strThreadPtr;
    for (std::list<Entity*>::iterator it = simulator->getEntities()->begin(); it != simulator->getEntities()->end(); it++) {
        strThreadPtr = (*it)->getAttribute("ThreadPtr")->getValue();
        if (strThreadPtr == strNext) {
            simulator->insertEvent(time, module, (*it));
            //break;
        } else if (strThreadPtr == strPrevious) {
            simulator->removeEventsOfEntity((*it));
            //break;
        }
    }

}

void CPU::restore_context(Thread* next) {
    Simulator* simulator = Simulator::getInstance();
    double time = simulator->getTnow();
    time += Traits<CPU>::context_switch_overhead;
    Debug::cout(Debug::Level::trace, "CPU[" + std::to_string(_staticActualInstance) + "]::restore_context(" + std::to_string(reinterpret_cast<unsigned long> (next)) + ")"); // will happen at time [" + std::to_string(time) + "]");

    Module* module = simulator->getModel()->getModule("InvokeThreadExec"); // must match name given on main())
    std::string strNext = std::to_string(reinterpret_cast<unsigned long> (next));
    std::string strThreadPtr;
    bool found = false;
    for (std::list<Entity*>::iterator it = simulator->getEntities()->begin(); it != simulator->getEntities()->end(); it++) {
        Debug::cout(Debug::Level::trace, "test");
        strThreadPtr = (*it)->getAttribute("ThreadPtr")->getValue();
        if (strThreadPtr == strNext) {
            simulator->insertEvent(time, module, (*it));
            found = true;
            break;
        }
    }
    if (!found) {
        simulator->insertEvent(time, module, next->getProcess()->getEntity());
    }
}

unsigned int CPU::getInstance() {

    return _staticActualInstance;
}

void CPU::setInstance(unsigned int _instance) {
    CPU::_staticActualInstance = _instance;
}