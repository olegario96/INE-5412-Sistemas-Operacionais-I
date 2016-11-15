/*
 * File:   ModuleCreate.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 10:33 AM
 */

#include "ModuleCreate.h"
#include "Simulator.h"
#include "Simul_Debug.h"

#include <string>

ModuleCreate::ModuleCreate(std::string name, double firstCreation, unsigned int maxCreations, std::string timeBetweenCreations, std::string entityType, bool collectStatistics, unsigned int entitiesToCreate)
: SourceModule(name, firstCreation, maxCreations, timeBetweenCreations, entityType, collectStatistics) {
    _entitiesToCreate = entitiesToCreate;
    _entitiesCreatedSoFar = 0;
}

ModuleCreate::ModuleCreate(const ModuleCreate& orig) : SourceModule(orig) {
}

ModuleCreate::~ModuleCreate() {
}

void ModuleCreate::setEntitiesToCreate(unsigned int _entitiesToCreate) {
    this->_entitiesToCreate = _entitiesToCreate;
}

unsigned int ModuleCreate::getEntitiesToCreate() const {
    return _entitiesToCreate;
}

void ModuleCreate::do_run(Entity* entity) {
    Simulator* simulator = Simulator::getInstance();
    std::list<Module*>::iterator it = this->_nextModules->begin();
    std::string arrivalTime = std::to_string(simulator->getTnow());
    entity->getAttribute("ArrivalTime")->setValue(arrivalTime);
    // send entity forward in the model (to the first nextModule --usually it has only one next module (if-then-else and duplicate are exceptions)-- )
    (*it)->run(entity);
    // create more entities (if needed) and send them forward in the model
    for (unsigned int i = 1; i<this->_entitiesToCreate; i++) {
        Entity* newEntity = simulator->createEntity();
        newEntity->getAttribute("EntityType")->setValue(_entityType);
        newEntity->getAttribute("ArrivalTime")->setValue(arrivalTime);
        (*it)->run(newEntity);
    }
    // schedule next creation event
    double nextCreation = simulator->parse(this->_timeBetweenCreations);
    nextCreation += simulator->getTnow();
    std::string message;
    if (++_entitiesCreatedSoFar != _maxCreations) {
        Entity* newEntity = simulator->createEntity();
        newEntity->getAttribute("EntityType")->setValue(_entityType);
        simulator->insertEvent(nextCreation, this, newEntity);
        message = "Scheduling the creation of entity '" +std::to_string(newEntity->getId())+ "' for instant "+std::to_string(nextCreation);
        Debug::cout(Debug::Level::fine, message);
    }
}
