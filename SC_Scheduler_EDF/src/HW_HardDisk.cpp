/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_HardDisk.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 11:55
 */

#include "HW_HardDisk.h"
#include "Traits.h"
#include "Simulator.h"
#include "OperatingSystem.h"
#include "HW_Machine.h"

#include <list>
#include <stdlib.h>

HW_HardDisk::HW_HardDisk() {
    _hardDisk = new std::list<DiskSector*>();
    _headTrackPosition = 0;
}

HW_HardDisk::HW_HardDisk(const HW_HardDisk& orig) {
}

void HW_HardDisk::setCommandRegister(unsigned int _commandRegister) {
    this->_commandRegister = _commandRegister;
    unsigned int surface = _dataRegister % Traits<HW_HardDisk>::numSurfaces;
    unsigned int track = _dataRegister % Traits<HW_HardDisk>::numTracksPerSurface;
    unsigned int sector = _dataRegister % Traits<HW_HardDisk>::numSectorsPerTrack;
    unsigned int headMovement = abs(_headTrackPosition - track);
    double instantMovementFinished;
    Simulator* simulator;
    Entity* entity;
    bool found = false;
    switch (_commandRegister) {
        case GET_TOTALSECTORS:
            _dataRegister = Traits<HW_HardDisk>::numSurfaces * Traits<HW_HardDisk>::numTracksPerSurface * Traits<HW_HardDisk>::numSectorsPerTrack;
            break;
        case GET_SECTORSPERTRACK:
            _dataRegister = Traits<HW_HardDisk>::numSectorsPerTrack;
            break;
        case GET_SURFACES:
            _dataRegister = Traits<HW_HardDisk>::numSurfaces;
            break;
        case GET_TRACKSPERSURFACE:
            _dataRegister = Traits<HW_HardDisk>::numTracksPerSurface;
            break;
        case GET_HEADTRACKPOSITION:
            _dataRegister = _headTrackPosition;
            break;
        case GET_SECTORSIZE:
            _dataRegister = DISK_SECTOR_SIZE;
            break;
        case READ_LOGICALSECTOR:
            for (std::list<DiskSector*>::iterator it = _hardDisk->begin(); it != _hardDisk->end(); it++) {
                found = (*it)->surface == surface && (*it)->track == track && (*it)->sector == sector;
                if (found) {
                    for (unsigned int i = 0; i < DISK_SECTOR_SIZE; i++) {
                        _streamRegister[i] = (*it)->data[i];
                    }
                    break;
                }
            }
            if (!found) {
                // sector has not been written yet. Return zeroes
                for (unsigned int i = 0; i < DISK_SECTOR_SIZE; i++) {
                    _streamRegister[i] = 0;
                }
            }
            _headTrackPosition = track;
            // schedule an event to notify it's ready
            simulator = Simulator::getInstance();
            entity = simulator->getEntity();
            entity->getAttribute("MethodName")->setValue("HardDisk::interruptHandler()");
            instantMovementFinished = simulator->getTnow() + headMovement * Traits<HW_HardDisk>::sectorMovementTime;
            simulator->insertEvent(instantMovementFinished, HW_Machine::Module_HardwareEvent(), entity);
            break;
        case WRITE_LOGICALSECTOR:
            for (std::list<DiskSector*>::iterator it = _hardDisk->begin(); it != _hardDisk->end(); it++) {
                found = (*it)->surface == surface && (*it)->track == track && (*it)->sector == sector;
                if (found) {
                    for (unsigned int i = 0; i < DISK_SECTOR_SIZE; i++) {
                        (*it)->data[i] = _streamRegister[i];
                    }
                    break;
                }
            }
            if (!found) {
                // sector has not been written yet. Create it
                DiskSector* newSector = new DiskSector;
                newSector->surface = surface;
                newSector->track = track;
                newSector->sector = sector;
                for (unsigned int i = 0; i < DISK_SECTOR_SIZE; i++) {
                    newSector->data[i] = _streamRegister[i];
                }
                _hardDisk->insert(_hardDisk->begin(), newSector);
            }
            _headTrackPosition = track;
            // schedule an event to notify it's ready
            simulator = Simulator::getInstance();
            entity = simulator->getEntity();
            entity->getAttribute("MethodName")->setValue("HardDisk::interruptHandler()");
            instantMovementFinished = simulator->getTnow() + headMovement * Traits<HW_HardDisk>::sectorMovementTime;
            simulator->insertEvent(instantMovementFinished, HW_Machine::Module_HardwareEvent(), entity);
            break;
        default:
            // never should happen
            break;
    }
}

unsigned int HW_HardDisk::getStatusRegister() const {
    return _statusRegister;
}

void HW_HardDisk::setDataRegister(unsigned int _dataRegister) {
    this->_dataRegister = _dataRegister;
}

unsigned int HW_HardDisk::getDataRegister() const {
    return _dataRegister;
}

void HW_HardDisk::setStreamRegister(DiskSectorData _streamRegister) {
    for (unsigned int i = 0; i < DISK_SECTOR_SIZE; i++) {
        this->_streamRegister[i] = _streamRegister[i];
    }
}

HW_HardDisk::DiskSectorData* HW_HardDisk::getStreamRegister() {
    return &_streamRegister;

}

HW_HardDisk::~HW_HardDisk() {
}

