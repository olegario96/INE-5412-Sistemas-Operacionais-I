/*
 * File:   ModuleCreate.h
 * Author: cancian
 *
 * Created on September 27, 2015, 10:33 AM
 */

#ifndef MODULECREATE_H
#define	MODULECREATE_H

#include <string>

#include "SourceModule.h"

class ModuleCreate : public SourceModule {
public:
    ModuleCreate(std::string name, double firstCreation, unsigned int maxCreations, std::string timeBetweenCreations, std::string entityType, bool collectStatistics, unsigned int entitiesToCreate);
    ModuleCreate(const ModuleCreate& orig);
    virtual ~ModuleCreate();
    void setEntitiesToCreate(unsigned int _entitiesToCreate);
    unsigned int getEntitiesToCreate() const;
protected:
    virtual void do_run(Entity* entity);

private:
    unsigned int _entitiesToCreate;
    unsigned int _entitiesCreatedSoFar;
};

#endif	/* MODULECREATE_H */

