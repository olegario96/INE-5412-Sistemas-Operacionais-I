/*
 * File:   Debug.h
 * Author: cancian
 *
 * Created on September 27, 2015, 7:30 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include "Module.h"
#include "Simul_Entity.h"

#include <string>

class Debug {
public:

    enum Level {
        error,
        warning,
        trace,
        info,
        fine
    };

public:
    static void cout(Debug::Level level, Module* module, Entity* entity, std::string message);
    static void cout(Debug::Level level, std::string message);

    static bool isNewTime(double tnow) {
        static double _lastTime = -1.0;
        bool res = _lastTime < tnow;
        _lastTime = tnow;
        return res;
    }
private:
    Debug();
    Debug(const Debug& orig);
    virtual ~Debug();
};

#endif	/* DEBUG_H */

