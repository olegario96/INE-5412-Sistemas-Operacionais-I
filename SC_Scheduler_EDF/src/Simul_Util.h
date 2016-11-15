/*
 * File:   Util.h
 * Author: cancian
 *
 * Created on September 27, 2015, 8:06 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#include<string>

class Util {
public:

    enum TimeUnit {
        picosecond, nanosecond, microsecond, milisecond, second, minute, hour, day, week, month, year, century
    };

private:
    Util();
    Util(const Util& orig);
    virtual ~Util();
private:

};

#endif	/* UTIL_H */

