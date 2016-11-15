/*
 * File:   SourceModule.h
 * Author: cancian
 *
 * Created on September 27, 2015, 12:00 PM
 */

#ifndef SOURCEMODULE_H
#define	SOURCEMODULE_H

#include <string>
#include "Module.h"

class SourceModule : public Module {
public:
    SourceModule(std::string name, double firstCreation, unsigned int maxCreations, std::string timeBetweenCreations, std::string entityType, bool collectStatistics);
    SourceModule(const SourceModule& orig);
    virtual ~SourceModule();
public:
    void setTimeBetweenCreations(std::string _timeBetweenCreations);
    std::string getTimeBetweenCreations() const;
    void setMaxCreations(unsigned int _maxCreations);
    unsigned int getMaxCreations() const;
    void setFirstCreation(double _firstCreation);
    double getFirstCreation() const;
    void setEntityType(std::string _entityType);
    std::string getEntityType() const;
    void setCollectStatistics(bool _collectStatistics);
    bool isCollectStatistics() const;
protected:
    virtual void do_run(Entity* entity);
protected:
    double _firstCreation;
    unsigned int _maxCreations;
    std::string _timeBetweenCreations;
    std::string _entityType;
    bool _collectStatistics;
};

#endif	/* SOURCEMODULE_H */

