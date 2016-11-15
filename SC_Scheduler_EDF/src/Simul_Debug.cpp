/*
 * File:   Debug.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 7:30 PM
 */

#include <iostream>

#include "Simul_Debug.h"
#include "Simulator.h"
#include "Traits.h"

Debug::Debug() {
}

Debug::Debug(const Debug& orig) {
}

Debug::~Debug() {
}

void showAttributes(Entity * entity) {
    std::cout << " {";
    std::string type = entity->getAttribute("EntityType")->getValue();
    for (std::list<Attribute*>::iterator it = entity->getAttributes()->begin(); it != entity->getAttributes()->end(); it++) {
        if ((*it)->getName() != "EntityType") {
            std::cout << "" << (*it)->getName() << "=" << (*it)->getValue() << ",";
        }
    }
    std::cout << "}";
}

void Debug::cout(Debug::Level level, Module* module, Entity* entity, std::string message) {
    std::string strLevel;
    switch (level) {
        case 0: strLevel = "Error";
            if (!Traits<Debug>::error) return;
            break;
        case 1: strLevel = "Warning";
            if (!Traits<Debug>::warning) return;
            break;
        case 2: strLevel = "Trace";
            if (!Traits<Debug>::trace) return;
            break;
        case 3: strLevel = "Info";
            if (!Traits<Debug>::info) return;
            break;
        default: strLevel = "Fine";
            if (!Traits<Debug>::fine) return;
            break;
    }
    double tnow = Simulator::getInstance()->getTnow();
    if (Debug::isNewTime(tnow)) {
        std::cout << "[" << tnow << "]";
    }
    std::string entityType = entity->getAttribute("EntityType")->getValue();
    if (entityType.empty()) {
        entityType = "Entity";
    }
    std::cout << "\t<" << strLevel << "> Ent=" << entityType << "[" << entity->getId() << "]";
    if (Traits<Debug>::showEntityAttributes) {
        showAttributes(entity);
    }
    std::cout << ", Mod=" << module->getName() << ": " << message << "\n";
    //showEventsList();
}

void Debug::cout(Debug::Level level, std::string message) {
    std::string strLevel;
    switch (level) {
        case 0: strLevel = "Error";
            if (!Traits<Debug>::error) return;
            break;
        case 1: strLevel = "Warning";
            if (!Traits<Debug>::warning) return;
            break;
        case 2: strLevel = "Trace";
            if (!Traits<Debug>::trace) return;
            break;
        case 3: strLevel = "Info";
            if (!Traits<Debug>::info) return;
            break;
        default: strLevel = "Fine";
            if (!Traits<Debug>::fine) return;
            break;
    }
    double tnow = Simulator::getInstance()->getTnow();
    if (Debug::isNewTime(tnow)) {
        //if (!Traits<Debug>::info) {
        std::cout << "[" << Simulator::getInstance()->getTnow() << "]";
        //}
    }
    std::cout << "\t" << "<" << strLevel << "> " << message << "\n";
}

