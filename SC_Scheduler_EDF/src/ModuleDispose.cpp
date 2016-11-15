/*
 * File:   ModuleDeparture.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 10:33 AM
 */

#include "ModuleDispose.h"
#include "Simulator.h"
#include "Simul_Debug.h"

ModuleDispose::ModuleDispose(std::string name, bool collectStatistics) : Module(name) {
    _collectStatistics = collectStatistics;
}

ModuleDispose::ModuleDispose(const ModuleDispose& orig) : Module(orig) {
}

ModuleDispose::~ModuleDispose() {
}

void ModuleDispose::setCollectStatistics(bool _collectStatistics) {
    this->_collectStatistics = _collectStatistics;
}

bool ModuleDispose::isCollectStatistics() const {
    return _collectStatistics;
}

void ModuleDispose::do_run(Entity* entity) {
    Simulator *simulator = Simulator::getInstance();
    if (this->_collectStatistics) {
        /*@Todo: collect entity statistics*/
    }
    simulator->removeEntity(entity);
    Debug::cout(Debug::Level::fine, this, entity, "Entity was removed from system");
}