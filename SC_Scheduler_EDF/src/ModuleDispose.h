/*
 * File:   ModuleDeparture.h
 * Author: cancian
 *
 * Created on September 27, 2015, 10:33 AM
 */

#ifndef MODULEDISPOSE_H
#define	MODULEDISPOSE_H

#include "Module.h"

class ModuleDispose : public Module {
public:
    ModuleDispose(std::string name, bool collectStatistics);
    ModuleDispose(const ModuleDispose& orig);
    virtual ~ModuleDispose();
    void setCollectStatistics(bool _collectStatistics);
    bool isCollectStatistics() const;
protected:
    virtual void do_run(Entity* entity);
private:
    bool _collectStatistics;
};

#endif	/* MODULEDISPOSE_H */

