/*
 * File:   SourceModule.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 12:00 PM
 */

#include "SourceModule.h"

SourceModule::SourceModule(std::string name, double firstCreation, unsigned int maxCreations, std::string timeBetweenCreations, std::string entityType, bool collectStatistics)
: Module(name) {
    _firstCreation = firstCreation;
    _maxCreations = maxCreations;
    _timeBetweenCreations = timeBetweenCreations;
    _entityType = entityType;
    _collectStatistics = collectStatistics;
}

SourceModule::SourceModule(const SourceModule& orig) : Module(orig) {
}

SourceModule::~SourceModule() {
}

void SourceModule::setTimeBetweenCreations(std::string _timeBetweenCreations) {
    this->_timeBetweenCreations = _timeBetweenCreations;
}

std::string SourceModule::getTimeBetweenCreations() const {
    return _timeBetweenCreations;
}

void SourceModule::setMaxCreations(unsigned int _maxCreations) {
    this->_maxCreations = _maxCreations;
}

unsigned int SourceModule::getMaxCreations() const {
    return _maxCreations;
}

void SourceModule::setFirstCreation(double _firstCreation) {
    this->_firstCreation = _firstCreation;
}

double SourceModule::getFirstCreation() const {
    return _firstCreation;
}

void SourceModule::setEntityType(std::string _entityType) {
    this->_entityType = _entityType;
}

std::string SourceModule::getEntityType() const {
    return _entityType;
}

void SourceModule::setCollectStatistics(bool _collectStatistics) {
    this->_collectStatistics = _collectStatistics;
}

bool SourceModule::isCollectStatistics() const {
    return _collectStatistics;
}

void SourceModule::do_run(Entity* entity) { /* virtual */
}