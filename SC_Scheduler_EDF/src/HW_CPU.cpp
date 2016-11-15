/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_CPU.cpp
 * Author: cancian
 * 
 * Created on 31 de Agosto de 2016, 14:12
 */

#include "HW_CPU.h"
#include "HW_Machine.h"
#include "OperatingSystem.h"

HW_CPU::HW_CPU() {
    _registers[RegNum::zero] = 0;
    _registers[RegNum::pc] = 0x00;
    _registers[RegNum::sp] = 0xFF;
    _kernelMode = true;
}

HW_CPU::HW_CPU(const HW_CPU& orig) {
}

HW_CPU::~HW_CPU() {
}

HW_CPU::Register HW_CPU::readRegister(HW_CPU::RegNum registerNum) {
    if (registerNum <= RegNum::pc) { // pc is the last register
        return _registers[registerNum];
    } else {
        Debug::cout(Debug::Level::warning, "ERROR: reading invalid register: "+std::to_string(registerNum));
        return 0;
    }

}

void HW_CPU::writeRegister(HW_CPU::RegNum registerNum, HW_CPU::Register value) {

}

/*
 * Simulates the execution of one machine cycle (fetch instruction, decode it, execute,...)
 */
void HW_CPU::pulse() {
    // fetch instruction
    Information instruction = HW_Machine::MMU()->readMemory(this->_registers[RegNum::pc]);
    _registers[RegNum::pc]++;

    // decode instruction
    unsigned int opcode, rs, rt, rd, shamt, funct, addr;
    int constt;
    opcode = (instruction & 0xFC000000) >> IFormat::off_opcode;
    rs = (instruction & 0x03E00000) >> IFormat::off_rs;
    rt = (instruction & 0x001F0000) >> IFormat::off_rt;
    rd = (instruction & 0x0000F800) >> IFormat::off_rd;   // R-type only
    shamt = (instruction & 0x000007C0) >> IFormat::off_shamt; // R-type only
    funct = (instruction & 0x0000003F) >> IFormat::off_funct; // R-type only
    constt = (instruction & 0x0000FFFF) >> IFormat::off_const; // I-type only
    addr = (instruction & 0x03FFFFFF) >> IFormat::off_addr; // J-type only
    
    /*
    // FORCE: TOR TESTS PURPOSES ONLY
    _registers[a0] = 1; // Syscall number
    opcode = Opcode::RType;
    funct = Funct::syscall;
    */
    
     Debug::cout(Debug::Level::fine, "Executing instruction " + std::to_string(instruction));
            
    // execute instruction
    switch (opcode) {
        case Opcode::addi:
            _registers[rd] <= _registers[rs] + constt;
            break;
        case Opcode::andi:
            _registers[rd] <= _registers[rs] & constt;
            break;
        case Opcode::beq:
            if (_registers[rd] == _registers[rs]) {
                _registers[pc] <= _registers[pc] + constt;
            }
            break;
        case Opcode::bne:
            if (_registers[rd] != _registers[rs]) {
                _registers[pc] <= _registers[pc] + constt;
            }
            break;
        case Opcode::j:
            _registers[pc] = (_registers[pc] & 0xFC0000000) + addr;
            break;
        case Opcode::jal:
            _registers[ra] = _registers[pc];
            _registers[pc] = (_registers[pc] & 0xFC0000000) + addr;
            break;
        case Opcode::lui:
            _registers[rd] = constt << 16;
            break;
        case Opcode::lw:
            _registers[rd] = HW_Machine::MMU()->readMemory(_registers[rs] + constt);
            break;
        case Opcode::ori:
            _registers[rd] <= _registers[rs] | constt;
            break;
        case Opcode::slti:
            _registers[rd] <= (_registers[rs] < constt) ? 1 : 0;
            break;
        case Opcode::sw:
            HW_Machine::MMU()->writeMemory(_registers[rs] + constt, _registers[rd]);
            break;
        case Opcode::RType:
            switch (funct) {
                case Funct::add:
                    _registers[rd] = _registers[rs] + _registers[rt];
                    break;
                case Funct::andd:
                    _registers[rd] = _registers[rs] & _registers[rt];
                    break;
                case Funct::jr:
                    _registers[pc] = _registers[rs];
                    break;
                case Funct::nop:
                    break;
                case Funct::orr:
                    _registers[rd] = _registers[rs] | _registers[rt];
                    break;
                case Funct::slt:
                    _registers[rd] = (_registers[rs] < _registers[rt]) ? 1 : 0;
                    break;
                case Funct::sub:
                    _registers[rd] = _registers[rs] - _registers[rt];
                    break;
                case Funct::syscall:
                    // invoke an operating system syscall call
                    // ...
                    switch (_registers[a0]) {
                        case 0: // special system call to help creating a test application
                            OperatingSystem::ExecuteTestCode();
                            break;
                        case 1:
                            Process::exec();
                            break;
                        case 2:
                            Process::exit(0);
                            break;
                        case 3: //...
                            break;
                        // INSERT OTHERS SYSTEM CALLS
                        // ...
                        default:
                            // invalid system call
                            Debug::cout(Debug::Level::error, "Invalid system call: " + std::to_string(_registers[a0]));
                            break;
                    }

                    break;
                default:
                    // invalid function
                    Debug::cout(Debug::Level::error, "Invalid instruction filed funct: " + std::to_string(funct));
                    break;
            }
            break;
        default: // invalid opcode
            // exception throw
            Debug::cout(Debug::Level::error, "Invalid instruction filed opcode: " + std::to_string(opcode));
            break;
    }

    // check for interruptions

}