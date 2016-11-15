/*
 * File:   Simulator.cpp
 * Author: cancian
 *
 * Created on August 31, 2015, 7:43 AM
 */

#include "Simulator.h"
#include "Abstr_Process.h"
#include "Abstr_MemoryManager.h"
#include "SourceModule.h"
#include "OperatingSystem.h"

#include <iostream>
#include <iterator>

#include <sys/resource.h>
#include <sys/time.h>

std::default_random_engine Simulator::generator; //static

Simulator::Simulator() {
    // time
    // real CPU
    _sumUserCodeCpuTime = 0;
    // control
    _replicationIsInited = false;
    // Internal Components and Structures
    //_model = new Model();
    _entities = new std::list<Entity*>();
    _events = new std::list<Event*>();
}

Simulator::Simulator(const Simulator& orig) {

}

Simulator::~Simulator() {
}

void Simulator::_initSimulation() {

}

void Simulator::_initReplication() {
    // time
    _tnow = 0.0;
    //control
    _pauseRequested = false;
    // Real CPU
    _sumUserCodeCpuTime = 0;
    _events->clear();
    // init default entity attributes
    _model->addEntityAttribute(new Attribute("EntityType", ""));
    _model->addEntityAttribute(new Attribute("ArrivalTime", ""));
    //_model->addEntityAttribute(new Attribute("WaitingTime", ""));
    // create first entities
    double firstCreation;
    std::list<SourceModule*>* sources = _model->getSourceModules();
    for (std::list<SourceModule*>::iterator it = sources->begin(); it != sources->end(); it++) {
        firstCreation = (*it)->getFirstCreation();
        Entity* entity = createEntity();
        entity->getAttribute("EntityType")->setValue((*it)->getEntityType());
        insertEvent(firstCreation, (Module*) * it, entity);
    }
    _replicationIsInited = true;
}

void Simulator::_showReplicationStatistics() {
    std::cout << "User CPU ellapsed time (us): " << _sumUserCodeCpuTime << "\n";
    _replicationIsInited = false;
}

double Simulator::parse(std::string expression) {
    /*@Todo: Implement an expression parser*/
    return ::atof(expression.c_str());
}

void Simulator::step() {
    if (!_replicationIsInited) {
        _initSimulation();
        _initReplication();
    }
    try {
        _do_step();
    } catch (int ex) {
        std::cout << "ERROR: An exception number " << ex << " occurred. Simulation will stop.\n";
    }
}

void Simulator::_do_step() {
    Event* event;
    if ((!_events->empty()) && (_tnow < _model->getReplicationLength()) && (!parse(_model->getTerminatingCondition()))) {
        event = _getNextEvent();
        if (event->getTime() < _model->getReplicationLength()) {
            _processEvent(event);
        } else {
            _tnow = event->getTime();
        }
    }

}

void Simulator::_do_run() {
    std::cout << "Simulation of model\"" << this->_model->getName() << "\" is initing.\n";
    _initSimulation();
    for (unsigned int replicationNum = 1; replicationNum <= _model->getMaxReplications(); replicationNum++) {
        std::cout << "Replication " << replicationNum << " is starting.\n";
        _initReplication();
        _pauseRequested = false;
        while ((!_events->empty()) &&(!_stopRequested) && (_tnow < _model->getReplicationLength()) && (!parse(_model->getTerminatingCondition()))) {
            _do_step();
            if (Traits<Debug>::pauseOnEveryEvent) {
                std::cout << "[paused] ...press any key to continue...";
                std::cin.get();
                std::cout << std::endl;
                //system("pause");
            }
        }
        std::string causeTerminated;
        if (_events->empty()) {
            causeTerminated = "event queue is empty";
        } else if (_stopRequested) {
            causeTerminated = "user requested to stop";
        } else if (!(_tnow < _model->getReplicationLength())) {
            causeTerminated = "replication length was achieved";
        } else if (parse(_model->getTerminatingCondition())) {
            causeTerminated = "termination condition was achieved";
        } else causeTerminated = "unknown";
        std::cout << "Simulation has finished at time " << _tnow << " because " << causeTerminated << ".\n";
        _showReplicationStatistics();
        _showSimulationStatistics();
    }
    _showSimulationStatistics();
}

void Simulator::_showSimulationStatistics() {
    for (auto i = getAllProc()->front(); i != getAllProc()->back(); ++i) {
        auto statistics = i->getCpuTime();
        std::cout << "Statistics from process " << i->getId() << ".\n";
        std::cout << "CPU time: " << statistics._CPUTime << ".\n";
        std::cout << "Waiting time: " << statistics._waitingTime << ".\n";
        std::cout << "Blocked time: " << statistics._blockedTime << ".\n";
    }
}

void Simulator::run() {
    try {
        _do_run();
    } catch (int ex) {
        std::cout << "ERROR: An exception number " << ex << " occurred. Simulation will stop.\n";
    }
}

Model * Simulator::getModel() const {

    return _model;
}

double Simulator::getTnow() const {

    return _tnow;
}

void Simulator::insertEvent(double time, Module* module, Entity * entity) {
    Event* event = new Event(time, module, entity);
    _events->insert(_events->begin(), event);
    _events->sort([](const Event* a, const Event * b) {
        return a->getTime() < b->getTime();
    });

}

Event * Simulator::_getNextEvent() {
    if (Traits<Debug>::showListOfEvents) {
        std::string message = "List of Future Events: {";
        for (std::list<Event*>::iterator it = _events->begin(); it != _events->end(); it++) {
            message += "[" + std::to_string((*it)->getTime());
            message += "," + (*it)->getModule()->getName();
            message += +"," + std::to_string((*it)->getEntity()->getId()) + "] ";
        }
        message += "}";
        Debug::cout(Debug::Level::fine, message);
    }
    // real code
    Event* event = *_events->begin();
    _events->pop_front();
    return event;
}

double Simulator::_getRealCpuUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    double utime = (double) (usage.ru_stime.tv_sec * 1e6 + usage.ru_stime.tv_usec) / (double) (1e6);

    return utime;
}

void Simulator::pause() {
    _pauseRequested = true;
}

void Simulator::stop() {
    _stopRequested = true;
}

void Simulator::resume() {
    Debug::cout(Debug::Level::error, "Not implemented yet");
}

void Simulator::_processEvent(Event * event) {
    _actualEntity = event->getEntity();
    _actualModule = event->getModule();
    _tnow = event->getTime();
    // process event
    double tBegin, tEnd;
    tBegin = _getRealCpuUsage();
    try {
        _actualModule->run(_actualEntity); // invoke an specific module to run
    } catch (const int ex) {
        Debug::cout(Debug::Level::error, "ERROR in module " + _actualModule->getName() + " run()");
    }
    tEnd = _getRealCpuUsage();
    double ellapsed = tEnd - tBegin;
    _sumUserCodeCpuTime += ellapsed;
}

Entity * Simulator::createEntity(Entity * entity) {
    Entity* duplicatedEntity = new Entity(*entity);
    _entities->insert(_entities->begin(), duplicatedEntity);
    return duplicatedEntity;
}

void Simulator::removeEventsOfEntity(Entity * entity) {
    for (std::list<Event*>::iterator it = _events->begin(); it != _events->end(); it++) {
        if ((*it)->getEntity() == entity) {
            _events->erase(it);
            it = _events->begin();
        }
    }
}

Entity * Simulator::createEntity() {
    Entity* entity = new Entity();
    _entities->insert(_entities->begin(), entity);
    return entity;
}

Entity * Simulator::getEntity() {
    return _actualEntity;
}

Module* Simulator::getModule() {
    return _actualModule;
}

void Simulator::removeEntity(Entity * entity) {
    _entities->remove(entity);
    entity->~Entity();
}

void Simulator::setModel(Model * model) {
    _model = model;
}

std::list<Entity*>* Simulator::getEntities() const {
    return _entities;
}

std::list<Event*>* Simulator::getEvents() const {
    return _events;
}

int Simulator::generate_uniform_distribution(int min, int max) { // static
    std::uniform_int_distribution<int> uniform(min, max);
    return uniform(Simulator::generator);
}

//double Simulator::generate_uniform_distribution(double min, double max) { // static
//    std::uniform_real_distribution<double> uniform(min, max);
//    return uniform(Simulator::generator);
//}

/*
template <typename T> T Simulator::generate_uniform_distribution(T min, T max) { // static
    std::uniform_int_distribution<double> uniform(min, max);
    return uniform(Simulator::generator);
}
 */