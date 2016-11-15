/*
 * File:   Model.h
 * Author: cancian
 *
 * Created on September 1, 2015, 5:33 PM
 */

#ifndef MODEL_H
#define	MODEL_H

class Model;

#include <list>
#include <string>
#include "Module.h"
#include "SourceModule.h"
#include "Simul_Util.h"

class Model {
public:
    typedef Util::TimeUnit TimeUnit;
public:
    Model(std::string name);
    Model(const Model& orig);
    virtual ~Model();
public:
    std::list<Module*>::iterator addModule(Module *newModule);
    std::list<Module*>::iterator addSourceModule(SourceModule *newSourceModule);
    std::list<SourceModule*>* getSourceModules();
    std::list<Module*>* getModules();
    Module* getModule(std::string name);
public:
    void setReplicationLength(double _replicationLength);
    double getReplicationLength() const;
    void setWarmUpPeriod(double _warmUpPeriod);
    double getWarmUpPeriod() const;
    void setTimeUnitBase(TimeUnit _timeUnitBase);
    TimeUnit getTimeUnitBase() const;
    void setTerminatingCondition(std::string _terminatingCondition);
    std::string getTerminatingCondition() const;
    void setName(std::string _name);
    std::string getName() const;
    void addEntityAttribute(Attribute* attribute) const;
    std::list<Attribute*>* getEntityAttributes() const;
    void setMaxReplications(unsigned int _maxReplications);
    unsigned int getMaxReplications() const;
private:
    std::string _name;
    double _replicationLength;
    TimeUnit _timeUnitBase;
    double _warmUpPeriod;
    std::string _terminatingCondition;
    unsigned int _maxReplications;
private:
    std::list<Module*>* _modules;
    std::list<SourceModule*>* _sourceModules;
    std::list<Attribute*>* _entityAttributes;
};

#endif	/* MODEL_H */

