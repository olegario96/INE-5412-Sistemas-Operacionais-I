/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInvoke_SystemCall.h
 * Author: cancian
 *
 * Created on 18 de Setembro de 2016, 18:10
 */

#ifndef MODULEINVOKE_SYSTEMCALL_H
#define MODULEINVOKE_SYSTEMCALL_H

#include "Module.h"

class ModuleInvoke_HardwareEvent: public Module {
public:
    ModuleInvoke_HardwareEvent(std::string name);
    ModuleInvoke_HardwareEvent(const ModuleInvoke_HardwareEvent& orig);
    virtual ~ModuleInvoke_HardwareEvent();
private:

protected:
    virtual void do_run(Entity* entity);
};

#endif /* MODULEINVOKE_SYSTEMCALL_H */

