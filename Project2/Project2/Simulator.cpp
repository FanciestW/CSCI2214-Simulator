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
        lines.push_back(x);
    }
}

void Simulator::run(string output){
    
}
