  //
//  MainMemory.cpp
//  Project2
//
//  Created by William Lin on 4/25/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "MainMemory.hpp"

int MainMemory::loadProgramCode(string filename){
    ifstream input(filename);
    if(!input.is_open()) return 0;
    for(int i = 0; i < 5000; i++){
        char x, y;
        input >> x >> y;
        if(input.eof()) break;
        memory[i] = strtoul((string(1, x) + string(1, y)).c_str(), NULL, 16);
    }
    return 1;
}

/*
 Read from memory. 
 int addr is the address from memory to read from. 
 int W_B_H is an int that will determine how much memory to read.
 return what is read from memory
 */
int MainMemory::readMemory(int addr, int W_H_B){
    int toReturn = 0;
    switch(W_H_B){
        case 0:
            //word
            for(int i = 0; i < 4; i++) toReturn |= memory[addr + i] << 8 * abs(i - 3);
            break;
            
        case 1:
            //halfword
            for(int i = 0; i < 2; i++) toReturn |= memory[addr + i] << 8 * abs(i - 1);
            break;
            
        case 2:
            //byte
            toReturn |= memory[addr];
            break;
            
        default:
            return 0;
    }
    return toReturn;
}

/*
 Write to memory.
 int addr is the address from memory to read from.
 int W_B_H is an int that will determine how much memory to write.
 return 1 if successful write 0 if unsuccessful, -1 if bad W_H_B.
 */
int MainMemory::writeMemory(int addr, unsigned int data, int W_H_B){
    unsigned int mask = 0xFF000000;
    switch(W_H_B){
        case 0:
            //word
            for(int i = 0; i < 4; i++){
                memory[addr + i] = (data & mask) >> abs(i - 3) * 8;
                mask = mask >> 8;
            }
            break;
        case 1:
            //halfword
            mask = mask >> 16;
            for(int i = 0; i < 2; i++){
                memory[addr + i] = (data & mask) >> abs(i - 1) * 8;
                mask = mask >> 8;
            }
            break;
        case 2:
            //byte
            mask = mask >> 24;
            memory[addr] = data & mask;
            break;
        default:
            return -1;
    }
    return 1;
}
