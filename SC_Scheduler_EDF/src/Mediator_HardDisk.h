/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HD.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 14:46
 */

#ifndef HD_H
#define HD_H

#include "HW_HardDisk.h"

class DiskAccessRequest {
public:
    enum Operation {READ, WRITE};
public:
     DiskAccessRequest(Operation operation,HW_HardDisk::blockNumber blockNumber, HW_HardDisk::DiskSector* diskSector) {
         _operation = operation;
         _blockNumber = blockNumber;
         _diskSector = diskSector;
     }

     HW_HardDisk::DiskSector* GetDiskSector() const {
         return _diskSector;
     }

     HW_HardDisk::blockNumber GetBlockNumber() const {
         return _blockNumber;
     }

     Operation GetOperation() const {
         return _operation;
     }

     void SetPriority(int _priority) {
         this->_priority = _priority;
     }

     int GetPriority() const {
         return _priority;
     }
private:
    Operation _operation;
    HW_HardDisk::blockNumber _blockNumber;
    HW_HardDisk::DiskSector* _diskSector;
    int _priority; // this attribute MUST BE the one used to sort the Schelung_Queue, no matter the scheduler algorithm
};

class HardDisk {
    friend class ModuleInvoke_HardwareEvent;
    friend class ProblemTester;
public:
    HardDisk(unsigned int instance);
    HardDisk(const HardDisk& orig);
    virtual ~HardDisk();
public:
    void flush();

    void writeBlock(DiskAccessRequest* request);
    
    void readBlock(DiskAccessRequest* request);
    
    void accessBlock(DiskAccessRequest* request); // more generic than read or write. Invoke read or write inside it

    void setBlockSize(const unsigned int blocksize);

    /**
     * Returns the size of one disk block
     * @return The number of bytes per block
     */
    unsigned int getBlockSize();

    /**
     * Sets the maximum number of blocks per disk, used to define disk total space.
     * @param maxBlocks The maximum number of blocks per disk
     */
    void setMaxBlocks(const HW_HardDisk::blockNumber maxBlocks);

    /**
     * Returns the number of blocks per disk
     * @return The number of blocks per disk
     */
    HW_HardDisk::blockNumber getMaxBlocks();


private:
    unsigned int _instance;
    unsigned int _blocksize;  // should be equal to the HD sector size for simplicity
    HW_HardDisk::blockNumber _maxBlocks;
private:
    static void interrupt_handler();
};

#endif /* HD_H */

