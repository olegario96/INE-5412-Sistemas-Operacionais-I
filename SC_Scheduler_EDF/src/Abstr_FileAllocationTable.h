/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileAllocationTable.h
 * Author: cancian
 *
 * Created on 9 de Setembro de 2016, 10:14
 */

#ifndef FILEALLOCATIONTABLE_H
#define FILEALLOCATIONTABLE_H

#include "Mediator_HardDisk.h"


/**
 * Base class for file attributes. Includes only the name, size and type of a file.
 */
class FileAttributes {
public:
    FileAttributes();
public:
    enum fileType {a,d,c,b,l};
    
    char* getFilename();
    void setFilename(char* filename);
    unsigned long getSize();
    void setSize(unsigned long size);
    fileType getType();
    void setType(fileType type);
private:
    char* filename;
    unsigned long size;
    fileType type;
};


/**
 * An entry in a FAT (@class {FileAllocationTable} ), representing a file (regular, directory or device) in the disk.
 * @param inode Unique id for the file
 * @param block The first block where the file is allocated using a @class FileAllocator algorithm.
 * @param attributes File attributes.
 */
class FileAllocationEntry {
public: 
    typedef unsigned int fileIdentifier;
public:
    FileAllocationEntry(fileIdentifier inode, HW_HardDisk::blockNumber block, FileAttributes attributes);
public:
    fileIdentifier getNode();
    HW_HardDisk::blockNumber getBlock();
    FileAttributes getAttributes();
    void setName(fileIdentifier inode);
    void setBlock(HW_HardDisk::blockNumber block);
    void setAttributes(FileAttributes attributes);    
private:
    fileIdentifier inode;
    HW_HardDisk::blockNumber block;
    FileAttributes attributes;
};

class FileAllocationTable {
public:
    FileAllocationTable(HardDisk* disk);
    FileAllocationTable(const FileAllocationTable& orig);
public:
    void addFileEntry(FileAllocationEntry fatEntry);
    void removeFileEntryByNode(FileAllocationEntry::fileIdentifier inode);
    void removeFileEntryByRank(unsigned int rank);
    FileAllocationEntry getFileEntryByNode(FileAllocationEntry::fileIdentifier inode);
    FileAllocationEntry getFileEntryByRank(unsigned int rank);
    void setFileEntry(unsigned int rank, FileAllocationEntry fatEntry);
private:
    HardDisk* disk;
};


#endif /* FILEALLOCATIONTABLE_H */

