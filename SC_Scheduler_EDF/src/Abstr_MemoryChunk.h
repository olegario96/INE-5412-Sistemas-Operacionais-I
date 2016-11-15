/*
 * File:   MemorySegment.h
 * Author: cancian
 *
 * Created on September 27, 2015, 10:50 AM
 */

#ifndef MEMORYSEGMENT_H
#define	MEMORYSEGMENT_H

#include "HW_MMU.h"

class MemoryChunk {
    friend class ProblemTester;
    
    typedef HW_MMU::PhysicalAddress PhysicalAddress;
    typedef HW_MMU::LogicalAddress LogicalAddress;
public:
    
    MemoryChunk(LogicalAddress beginAddress, unsigned int size, bool isExecutable, bool isReadable, bool isWritable) {
        _beginLogicalAddress = beginAddress;
        _size = size;
        _isReadable = isReadable;
        _isWritable = isWritable;
        _isExecutable = isExecutable;
    }

    MemoryChunk(const MemoryChunk& orig) {
    }

    virtual ~MemoryChunk() {
    }

    unsigned int getSize() const {
        return _size;
    }

    bool isIsExecutable() const {
        return _isExecutable;
    }

    bool isIsWritable() const {
        return _isWritable;
    }

    bool isIsReadable() const {
        return _isReadable;
    }

    PhysicalAddress getBeginPhysicalAddress() const {
        return _beginPhysicalAddress;
    }

    LogicalAddress getBeginLogicalAddress() const {
        return _beginLogicalAddress;
    }


private:
    
    unsigned long _size;
    bool _isReadable;
    bool _isWritable;
    bool _isExecutable;
    
    LogicalAddress _beginLogicalAddress;
    PhysicalAddress _beginPhysicalAddress;
};

#endif	/* MEMORYSEGMENT_H */

