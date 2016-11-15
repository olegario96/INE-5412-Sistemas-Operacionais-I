/*
 * File:   Module.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 11:20 AM
 */

#include "Module.h"
#include "Simulator.h"
#include "Simul_Debug.h"

Module::Module(std::string name) {
    _name = name;
    _nextModules = new std::list<Module*>();
}

Module::Module(const Module& orig) {
}

Module::~Module() {
}

void Module::run(Entity* entity) {
    Debug::cout(Debug::Level::fine, this, entity, "Entity has arrived to module");
    do_run(entity);
}

void Module::addNextModule(Module* nextModule) {
    //_nextModules->insert(_nextModules->begin(), nextModule);
    _nextModules->insert(_nextModules->end(), nextModule);
}

void Module::setName(std::string _name) {
    this->_name = _name;
}

std::string Module::getName() const {
    return _name;
}

std::list<Module*>* Module::getNextModules() const {
    return _nextModules;
}

void Module::do_run(Entity* entity) {

}