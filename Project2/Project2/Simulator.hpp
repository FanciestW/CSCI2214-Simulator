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
    vector<unsigned int> lines;
    
public:
    ~Simulator() = default;
    Simulator(string);
    void run(string);
    
};

#endif /* Simulator_hpp */
