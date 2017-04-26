//
//  MainMemory.hpp
//  Project2
//
//  Created by William Lin on 4/25/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#ifndef MainMemory_hpp
#define MainMemory_hpp

#include "tools.hpp"

class MainMemory{
private:
    unsigned char memory[5000] = {};
    
public:
    ~MainMemory() = default;
    MainMemory(){}
    int loadProgramCode(string);
    int readMemory(int, int);
    int writeMemory(int, unsigned int, int);
};

#endif /* MainMemory_hpp */
