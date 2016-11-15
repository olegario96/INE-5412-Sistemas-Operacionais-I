/*
 * File:   Entity.cpp
 * Author: cancian
 *
 * Created on September 27, 2015, 10:30 AM
 */

#include <list>

#include "Simul_Entity.h"
#include "Simulator.h"

Entity::Entity() {
    this->_id = Entity::getNewId();
    this->_attributes = new std::list<Attribute*>();
    std::list<Attribute*>* entAttrs = Simulator::getInstance()->getModel()->getEntityAttributes();
    for (std::list<Attribute*>::iterator it = entAttrs->begin(); it != entAttrs->end(); it++) {
        Attribute* newAttribute = new Attribute((*it)->getName(), (*it)->getValue()); //@Todo: Should use copy constructor
        _attributes->insert(_attributes->begin(), newAttribute);
    }
}

std::list<Attribute*>* Entity::getAttributes() const {

    return _attributes;
}

Attribute* Entity::getAttribute(std::string name) const {
    Attribute* attr;
    for (std::list<Attribute*>::iterator it = _attributes->begin(); it != _attributes->end(); it++) {
        attr = (*it);
        if (attr->getName() == name) {
            return attr;
        }
    }
    return nullptr;
}

void Entity::setPointer(void* _pointer) {

    this->_pointer = _pointer;
}

void* Entity::getPointer() const {

    return _pointer;
}

unsigned int Entity::getId() const {

    return _id;
}

Entity::Entity(const Entity& orig) {
    _id = Entity::getNewId();
    _pointer = orig._pointer;
    _attributes = new std::list<Attribute*>();
    for (std::list<Attribute*>::iterator it = orig._attributes->begin(); it != orig._attributes->end(); it++) {
        Attribute* newAttr = new Attribute(*(*it));
        _attributes->insert(this->_attributes->end(), newAttr);
    }
}

Entity::~Entity() {
}

