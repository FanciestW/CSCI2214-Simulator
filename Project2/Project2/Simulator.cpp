//
//  Simulator.cpp
//  Project2
//
//  Created by William Lin on 4/20/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Simulator.hpp"

Simulator::Simulator(string filename){
    ifstream input(filename);
    if(!input.is_open()) fatal("Input File Error");
    for(;;){
        string line;
        getline(input, line);
        if(input.eof()) break;
        unsigned int x = strtoul(line.substr(0, 8).c_str(), NULL, 16);
        ir.push_back(x);
    }
}

void Simulator::run(){
    
}

void Simulator::printState(){
    printf("Register File:\n");
    for(int i = 0; i < 32; i++) printf("R%i: 0x%02X ", i, registers[i]);
    printf("\nMemory Registers:\n");
    printf("MDR: 0x%02X MAR: 0x%02X\nHardware Registers:\n", mdr, mar);
    for(int i = 0; i < ir.size(); i++) printf("IR%i: 0x%08X ", i, ir[i]);
    printf("\nPC: 0x%02X\nData Bus:\n", pc);
    printf("S1: 0x%02X S2: 0x%02X Dest: 0x%02X Addr: 0x%02X Data: 0x%02X\n", s1, s2, dest, addr, data);
    printf("Register Buffers:\nA: 0x%02X B: 0x%02X C: 0x%02X\n", a, b, c);
}
