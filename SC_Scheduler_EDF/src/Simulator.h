/*
 * File:   Simulator.h
 * Author: cancian
 *
 * Created on August 31, 2015, 7:43 AM
 */

#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <list>
#include <random>
#include <string>
#include "Model.h"
#include "Simul_Event.h"
#include "Abstr_Process.h"
#include <sys/resource.h>
#include <sys/time.h>


class Simulator {
    friend class ProblemTester;
public:

    static Simulator* getInstance() {
        static Simulator* _singleton;
        if (!_singleton) {
            _singleton = new Simulator();
        }
        return _singleton;
    }
    static std::default_random_engine generator;
    static int generate_uniform_distribution(int min, int max);
    //static double generate_uniform_distribution(double min, double max);
    //template <typename T> static T generate_uniform_distribution(T min, T max);
public:
    void run();
    void step();
    void pause();
    void stop();
    void resume();
public:
    double parse(std::string expression);
public: // manage structures
    void insertEvent(double time, Module* module, Entity* entity);
    Entity* createEntity();
    Entity* createEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void removeEventsOfEntity(Entity* entity);
public: // getters and setters
    Model* getModel() const;
    double getTnow() const;
    Entity* getEntity();
    Module* getModule();
    void setModel(Model* _model);
    std::list<Entity*>* getEntities() const;
    std::list<Event*>* getEvents() const;
    static std::list<Process*>* getAllProc() { // return the listr of all processes in the system
        static std::list<Process*>* all_proc;
        if (all_proc == nullptr) {
            all_proc = new std::list<Process*>();
        }
        return all_proc;
    }
public:
private: // constructors and destructors
    Simulator();
    Simulator(const Simulator& orig);
    virtual ~Simulator();
private: // 1:n
    std::list<Event*>* _events;
    std::list<Entity*>* _entities;
private: // associated objects
    Model* _model;
    Entity* _actualEntity;
    Module* _actualModule;
private: //control
    bool _pauseRequested;
    bool _stopRequested;
    bool _replicationIsInited;
private: //time
    double _tnow;
    // Real CPU interval
    double _sumUserCodeCpuTime;
private:
    void _initReplication();
    void _initSimulation();
    void _showReplicationStatistics();
    void _showSimulationStatistics();
    void _processEvent(Event* event);
    double _getRealCpuUsage();
    Event* _getNextEvent();
    void _do_run();
    void _do_step();

private:

};

#endif	/* SIMULATOR_H */

