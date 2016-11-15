/*
 * File:   Model.cpp
 * Author: cancian
 *
 * Created on September 1, 2015, 5:33 PM
 */

#include "Model.h"
#include <list>

Model::Model(std::string name) {
    _name = name;
    _replicationLength = 0.0;
    _timeUnitBase = TimeUnit::second;
    _warmUpPeriod = 0.0;
    _terminatingCondition = "0"; // always false
    _maxReplications = 1;

    _modules = new std::list<Module*>();
    _sourceModules = new std::list<SourceModule*>(); /* @Todo: a _disposeModules is missing */
    _entityAttributes = new std::list<Attribute*>();
}

void Model::setTerminatingCondition(std::string _terminatingCondition) {
    this->_terminatingCondition = _terminatingCondition;
}

std::string Model::getTerminatingCondition() const {
    return _terminatingCondition;
}

void Model::setName(std::string _name) {
    this->_name = _name;
}

std::string Model::getName() const {
    return _name;
}

Model::Model(const Model& orig) {
}

Model::~Model() {
}

std::list<Module*>::iterator Model::addModule(Module *newModule) {
    return _modules->insert(_modules->begin(), newModule);
}

std::list<Module*>::iterator Model::addSourceModule(SourceModule *newSourceModule) {
    _sourceModules->insert(_sourceModules->begin(), newSourceModule);
    return _modules->insert(_modules->begin(), (Module*) newSourceModule);
}

std::list<SourceModule*>* Model::getSourceModules() {
    return _sourceModules;
}

void Model::setReplicationLength(double _replicationLength) {
    this->_replicationLength = _replicationLength;
}

double Model::getReplicationLength() const {
    return _replicationLength;
}

void Model::setWarmUpPeriod(double _warmUpPeriod) {
    this->_warmUpPeriod = _warmUpPeriod;
}

double Model::getWarmUpPeriod() const {
    return _warmUpPeriod;
}

void Model::setTimeUnitBase(TimeUnit _timeUnitBase) {
    this->_timeUnitBase = _timeUnitBase;
}

std::list<Module*>* Model::getModules() {
    return this->_modules;
}

Module* Model::getModule(std::string name) {
    Module* result;
    for (std::list<Module*>::iterator it = this->_modules->begin(); it != _modules->end(); it++) {
        result = (*it);
        if (result->getName() == name) {
            return result;
        }
    }
    return nullptr;
}

void Model::addEntityAttribute(Attribute* attribute) const {
    for (std::list<Attribute*>::iterator it = _entityAttributes->begin(); it != _entityAttributes->end(); it++) {
        if ((*it)->getName() == attribute->getName()) {
            return;
        }
    }
    _entityAttributes->insert(_entityAttributes->begin(), attribute);
}

std::list<Attribute*>* Model::getEntityAttributes() const {
    return _entityAttributes;
}

void Model::setMaxReplications(unsigned int _maxReplications) {
    this->_maxReplications = _maxReplications;
}

unsigned int Model::getMaxReplications() const {
    return _maxReplications;
}