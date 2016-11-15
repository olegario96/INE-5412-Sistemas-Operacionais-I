/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Application.h
 * Author: cancian
 *
 * Created on 31 de Agosto de 2016, 14:18
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <list>
#include <iostream>

#include "Mediator_CPU.h"

class Application {
public:
    typedef HW_MMU::Information Information;
public:
    Application();
    Application(const Application& orig);
    virtual ~Application();
public:
    void addCode(Information instruction);
    void addData(Information data);
    std::list<Information> getCode();
    std::list<Information> getData();
private:
    std::list<Information> _code;
    std::list<Information> _data;

public:

    static Application* DefaultBootApplication() {
        Application* app = new Application();;
        CPU::Information instruction;
        // this dummy boot application just keeps invoking system calls over and over again (always incrementing the system call number: it cant'end well..).
   
        // 0: addi a0, zero, 0 (syscall 0 = ExecuteTestCode )
        instruction =   (CPU::Opcode::addi << CPU::IFormat::off_opcode) + 
                        (CPU::RegNum::a0 << CPU::IFormat::off_rd) + 
                        (CPU::RegNum::zero << CPU::IFormat::off_rs) + 
                        (0 << CPU::IFormat::off_const);
        app->addCode(instruction);
        // 1: syscall 
        instruction =   (CPU::Opcode::RType << CPU::IFormat::off_opcode) + (
                        CPU::Funct::syscall << CPU::IFormat::off_funct);
        app->addCode(instruction);
        // 2: addi a0, a0, 1
        instruction =   (CPU::Opcode::addi << CPU::IFormat::off_opcode) + 
                        (CPU::RegNum::a0 << CPU::IFormat::off_rd) + 
                        (CPU::RegNum::a0 << CPU::IFormat::off_rs) + 
                        (1 << CPU::IFormat::off_const);
        app->addCode(instruction);
        // 3: j 1
        instruction =   (CPU::Opcode::j << CPU::IFormat::off_opcode) + 
                        (1 << CPU::IFormat::off_addr);
        app->addCode(instruction);
        return app;
    }
};

#endif /* APPLICATION_H */

