/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_HardDisk.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 11:55
 */

#ifndef HW_HARDDISK_H
#define HW_HARDDISK_H

#include <list>

#define DISK_SECTOR_SIZE 64

class HW_HardDisk {
    friend class ProblemTester;
public:
    typedef unsigned char DiskSectorData[DISK_SECTOR_SIZE];
    typedef unsigned int blockNumber;
public:

    struct DiskSector {
        DiskSectorData data;
        unsigned int surface;
        unsigned int track;
        unsigned int sector;
    };

    enum HDCommand {
        GET_SURFACES          = 0x00000001,
        GET_TRACKSPERSURFACE  = 0x00000002,
        GET_SECTORSPERTRACK   = 0x00000004,
        GET_TOTALSECTORS      = 0x00000008,
        GET_HEADTRACKPOSITION = 0x00000010,
        GET_SECTORSIZE        = 0x00000020,
        READ_LOGICALSECTOR    = 0x00000040,
        WRITE_LOGICALSECTOR   = 0x00000080
    };
public:
    HW_HardDisk();

    HW_HardDisk(const HW_HardDisk& orig);
    virtual ~HW_HardDisk();
    void setCommandRegister(unsigned int _commandRegister);
    unsigned int getStatusRegister() const;
    void setDataRegister(unsigned int _dataRegister);
    unsigned int getDataRegister() const;
    void setStreamRegister(DiskSectorData _streamRegister);
    DiskSectorData* getStreamRegister();
private:
    DiskSectorData _streamRegister;
    unsigned int _dataRegister;
    unsigned int _commandRegister;
    unsigned int _statusRegister;
private:
    std::list<DiskSector*> *_hardDisk;
    unsigned int _headTrackPosition;
};

#endif /* HW_HARDDISK_H */

