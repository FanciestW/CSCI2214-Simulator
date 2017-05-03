//
//  Simulator.cpp
//  Project2
//
//  Created by William Lin on 4/20/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Simulator.hpp"

void Simulator::run(){
    for(;;){
        step1();
        if(ir == 0) break;
        step2();
        switch(getInstrType(opcode)){
            case 0: runRtype(); break; //Handles All R types;
            case 1: runJtype(); break;
            case 2:
                //runItypeJ()
                break;
            case 3:
                //branch steps
                break;
            case 4:
                runItypeALU(); break;
                break;
            case 5: runLoadInstr(); break;
            case 6: runStoreInstr(); break;
            default:
                fatal("Bad opcode");
                break;
        }
        printStateHex();
    }
}

void Simulator::step1(){
    setPCMARselect(0);
    readMem(1, 0);
    setIRload(1);
}

void Simulator::step2(){
    setPCoeS1(1);
    setS2op(7);
    setALUop(0);
    setPCload(1);
    setAload(1);
    setBload(1);
}

void Simulator::runRtype(){
    setAoe(1);
    setBoe(1);
    setS2op(0);
    switch(opcodeALU){
        case 4: setALUop(8); break;
        case 6: setALUop(10); break;
        case 7: setALUop(12); break;
        case 18: setALUop(21); break;
        case 19: setALUop(25); break;
        case 20: setALUop(27); break;
        case 21: setALUop(23); break;
        case 32: setALUop(0); break;
        case 33: setALUop(28); break;
        case 34: setALUop(1); break;
        case 35: setALUop(29); break;
        case 36: setALUop(4); break;
        case 37: setALUop(5); break;
        case 38: setALUop(6); break;
        case 40: setALUop(16); break;
        case 41: setALUop(18); break;
        case 42: setALUop(20); break;
        case 43: setALUop(24); break;
        case 44: setALUop(26); break;
        case 45: setALUop(22); break;
        default: fatal("Bad opcodeALU"); break;
    }
    setCload(1);
    setREGselect(0);
    setREGload(1);
}

void Simulator::runJtype(){
    b = offset;
    setBoe(1);
    setPCoeS1(1);
    setS2op(5);
    setALUop(0);
    setPCload(1);
}

void Simulator::runLoadInstr(){
    //TODO::Test Load Instr
    //Step 3:
    setAoe(1);
    setIRoeS2(1);
    setS2op(3);
    setALUop(0);
    setMARload(1);
    setPCMARselect(1);
    switch(opcode){
        case 32: readMem(1, 2); break;
        case 33: readMem(1, 1); break;
        case 35: readMem(1, 0); break;
    }
    setMDRload(1);
    setMDRoeS2(1);
    setS2op(0);
    setALUop(3);
    setCload(1);
    setREGselect(1);
    setREGload(1);
}

void Simulator::runStoreInstr(){
    //TODO::Code for store instructions
    
}

void Simulator::runItypeALU(){
    setAoe(1);
    setIRoeS2(1);
    if(opcode == 9 && opcode == 11) setS2op(4);
    else setS2op(3);
    switch(opcode){
        case 8: setALUop(0); break;
        case 9: setALUop(0); break;
        case 10: setALUop(1); break;
        case 11: setALUop(1); break;
        case 12: setALUop(4); break;
        case 13: setALUop(5); break;
        case 14: setALUop(6); break;
        default: break;
    }
    setCload(1);
    setREGselect(1);
    setREGload(1);
}

void Simulator::setPCMARselect(bool pcmar){
    PCMARselect = pcmar;
    if(PCMARselect) addr = mar;
    else addr = pc;
}

void Simulator::readMem(bool read, int op){
    if(read){
        MemRead = 1;
        data = mem.readMemory(addr, op);
        mdrMux = data;
    }
}

void Simulator::setIRload(bool load){
    if(load){
        ir = data;
        rd = (ir & 0x0000F800) >> 11;
        rs1 = (ir & 0x03E00000) >> 21;
        rs2 = (ir & 0x001F0000) >> 16;
        imm = (ir & 0x0000FFFF);
        offset = (ir & 0x03FFFFFF);
        opcode = ir >> 26;
        opcodeALU = ir & 0x000007FF;
    }
}

void Simulator::setS2op(int op){
    //TODO::Test if s2op works
    switch(op){
        case 1:
            if((s2 & 0x00000080) == 128) s2 = s2 | 0xFFFFFF00;
            else s2 = s2 & 0x000000FF;
            break;
        case 3:
            if((s2 & 0x00008000) == 32768) s2 = s2 | 0xFFFF0000;
            else s2 = s2 & 0x0000FFFF;
            break;
        case 5:
            if((s2 & 0x02000000) == 33554432) s2 = s2 | 0xFC000000;
            else s2 = s2 & 0x03FFFFFF;
            break;
        case 6: s2 = (unsigned)16; break;
        case 7: s2 = (unsigned)4; break;
        default: break;
    }
    S2op = op;
}

void Simulator::setALUop(int op){
    switch(op){
        case 0: dest = s1 + s2; break;
        case 1: dest = s1 - s2; break;
        case 2: dest = s1; break;
        case 3: dest = s2; break;
        case 4: dest = s1 & s2; break;
        case 5: dest = s1 | s2; break;
        case 6: dest = s1 ^ s2; break;
        case 8: dest = s1  << (s2 % 8); break;
        case 10: dest = s1 >> (s2 % 8); break;
        case 16: dest = (s1 == s2); break;
        case 18: dest = (s1 != s2); break;
        case 20: dest = (s1 < s2); break;
        case 21: dest = (unsigned)(s1 < s2); break;
        case 22: dest = (s1 >= s2); break;
        case 23: dest = (unsigned)(s1 >= s2); break;
        case 24: dest = (s1 > s2); break;
        case 25: dest = (unsigned)(s1 > s2); break;
        case 26: dest = (s1 <= s2); break;
        case 27: dest = (unsigned)(s1 <= s2); break;
        case 28: dest = (unsigned)(s1 + s2); break;
        case 29: dest = (unsigned)(s1 - s2); break;
        default: fatal("Bad ALUop"); break;
    }
    if(dest == 0) Zflag = true;
}

//Designate where DMX will store C
void Simulator::setREGselect(int sel){
    switch(sel){
        case 0: REGselect = 0; DMX = rd; break;
        case 1: REGselect = 1; DMX = rs2; break;
        case 2: REGselect = 2; DMX = 31; break;
    }
}

//Print to console the state of Simulator in Hex
void Simulator::printStateHex(){
    cout << string(80, '=') << endl;
    printf("Register File:\n");
    for(int i = 0; i < 32; i++) printf("R%i: 0x%02X ", i, registers[i]);
    printf("\nMemory Registers:\n");
    printf("MDR: 0x%02X MAR: 0x%02X\nHardware Registers:\n", mdr, mar);
    printf("IR: 0x%08X ", ir);
    printf("\nPC: 0x%02X\nData Bus:\n", pc);
    printf("S1: 0x%02X S2: 0x%02X Dest: 0x%02X Addr: 0x%02X Data: 0x%02X\n", s1, s2, dest, addr, data);
    printf("Register Buffers:\nA: 0x%02X B: 0x%02X C: 0x%02X\n", a, b, c);
    cout << string(80, '=') << endl;
}

//Print to console the state of Simulator in Decimal
void Simulator::printStateDec(){
    printf("Register File:\n");
    for(int i = 0; i < 32; i++) printf("R%i: %i ", i, registers[i]);
    printf("\nMemory Registers:\n");
    printf("MDR: %i MAR: %i\nHardware Registers:\n", mdr, mar);
    printf("IR: %i ", ir);
    printf("\nPC: %i\nData Bus:\n", pc);
    printf("S1: %i S2: %i Dest: %i Addr: %i Data: %i\n", s1, s2, dest, addr, data);
    printf("Register Buffers:\nA: %i B: %i C: %i\n", a, b, c);
}

//return 0: Rtype; 1: J type; 2: Itype J 3: Branch; 4: Itype ALU; 5: load; 6: store; -1: no such op
int Simulator::getInstrType(int op){
    if(op == 0) return 0;
    else if(op == 2 || op == 3) return 1;
    else if(op == 18 || op == 19) return 2;
    else if(op == 4 || op == 5) return 3;
    else if(op > 7 && op < 15) return 4;
    else if(op ==15 || (op > 31 && op < 37)) return 5;
    else if((op > 23 && op < 30) || (op > 39 && op < 57)) return 6;
    else return -1;
}
