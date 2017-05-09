//
//  main.cpp
//  Project2
//
//  Created by William Lin on 4/13/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Simulator.hpp"

int main(int argc, const char * argv[]) {
    Simulator sim;
    sim.loadCode(argv[1]);
    sim.run(stoi(argv[2]));
    cout << "Simulation Complete" << endl;
}
