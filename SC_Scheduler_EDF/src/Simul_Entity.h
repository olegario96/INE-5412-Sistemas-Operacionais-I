/*
 * File:   Entity.h
 * Author: cancian
 *
 * Created on September 27, 2015, 10:30 AM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include<string>
#include<list>

class Attribute {
public:

    Attribute(std::string name, std::string value) {
        _name = name;
        _value = value;
    }

    Attribute(const Attribute& orig) {
        _name = orig._name; // @TODO: alloc new memory ???
        _value = orig._value;
    }

    virtual ~Attribute() {

    }
public:

    void setValue(std::string _value) {
        this->_value = _value;
    }

    std::string getValue() const {
        return _value;
    }

    std::string getName() const {
        return _name;
    }
private:
    std::string _name;
    std::string _value;
};

class Entity {
    friend class Simulator;
private:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
public:
    unsigned int getId() const;
    void setPointer(void* _pointer);
    void* getPointer() const;
    std::list<Attribute*>* getAttributes() const;
    Attribute* getAttribute(std::string name) const;
private:
    unsigned int _id;
    void* _pointer;
    std::list<Attribute*>* _attributes;
public:

    static unsigned int getNewId() {
        static unsigned int _lastId = 0;
        return ++_lastId;
    }
};

#endif	/* ENTITY_H */

