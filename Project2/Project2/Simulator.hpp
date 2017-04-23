//
//  Simulator.hpp
//  Project2
//
//  Created by William Lin on 4/20/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#ifndef Simulator_hpp
#define Simulator_hpp

#include "tools.hpp"

class Simulator{
private:
    vector<unsigned int> ir;
    int registers[32] = {};
    int pc = 0;
    int mdr = 0;
    int mar = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int s1 = 0;
    int s2 = 0;
    int dest = 0;
    int addr = 0;
    int data = 0;
    
    
public:
    ~Simulator() = default;
    Simulator(string);
    void run();
    void printState();
    
};

#endif /* Simulator_hpp */
