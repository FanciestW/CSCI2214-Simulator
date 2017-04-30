//
//  Simulator.cpp
//  Project2
//
//  Created by William Lin on 4/20/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Simulator.hpp"

void Simulator::run(){
    //TODO::Start to create the simulation
    
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

//return 0: Rtype; 1: J type; 2: Itype J 3: Branch; 4: Itype; 5: load; 6: store; -1: no such op
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
