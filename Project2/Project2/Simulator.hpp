//
//  Simulator.hpp
//  Project2
//
//  Created by William Lin on 4/20/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#ifndef Simulator_hpp
#define Simulator_hpp

#include "MainMemory.hpp"

class Simulator{
private:
    MainMemory mem;
    int registers[32] = {};
    int DMX;
    int rd, rs1, rs2, imm, offset = 0;
    int pc = 0;
    int ir = 0;
    int mdr = 0;
    int mdrMux = 0;
    int mar = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int s1 = 0;
    int s2 = 0;
    int dest = 0;
    int addr = 0;
    int data = 0;
    
    //Control Signals
    int S2op = -1;
    bool Zflag = false;
    int ALUop = -1;
    bool Cload = false;
    bool REGload = false;
    bool Aload = false;
    bool Aoe = false;
    bool Bload = false;
    bool Boe = false;
    int REGselect = -1;
    bool IRload = false;
    bool IRoeS1 = false;
    bool IRoeS2 = false;
    int opcode = -1;
    int opcodeALU = -1;
    bool Reset = false;
    bool PCload = false;
    bool PCoeS1 = false;
    bool PCMARselect = 0;
    bool MARload = false;
    bool MemRead = false;
    bool MDRload = false;
    bool MDRoeS2 = false;
    bool MemWrite = false;
    int MemOP = -1;
    
    //Control Signal Functions
    void setPCMARselect(bool);
    void readMem(bool, int);
    void setIRload(bool);
    void setPCoeS1(bool oe){ if(oe) s1 = pc; }
    void setS2op(int);
    void setALUop(int);
    void setPCload(bool load){ if(load) pc = dest; }
    void setAload(bool load){ if(load) a = registers[rs1]; }
    void setAoe(bool oe){ if(oe) s1 = a; }
    void setBload(bool load){ if(load) b = registers[rs2]; }
    void setBoe(bool oe){ if(oe) s2 = b; }
    void setCload(bool load){ if(load) c = dest; }
    void setREGload(bool load){ if(load) registers[DMX] = c; }
    void setREGselect(int);
    void setIRoeS1(bool oe){ if(oe) s1 = ir; }
    void setIRoeS2(bool oe){ if(oe) s2 = ir; }
    void setMARload(bool load){ if(load) mar = dest; }
    void setMDRload(bool load){ if(load) mdr = mdrMux; }
    void setMDRoeS2(bool oe){ if(oe) s2 = mdr; }
    void setMemRead(bool read){ if(read) mdrMux = data; }
    void setMemReadDest(bool read){ if(read) mdrMux = dest; }
    void setMemOP(int op){ MemOP = op; }
    void setMemWrite(bool);
    
    //Running Simulator Functions
    void step1();
    void step2();
    void runRtype();
    void runJtype();
    void runLoadInstr();
    void runStoreInstr();
    void runItypeALU();
    
    
public:
    ~Simulator() = default;
    Simulator(){}
    void run();
    void loadCode(string file){ mem.loadProgramCode(file); }
    void writeToMem(int addr, unsigned int data, int WHB){ mem.writeMemory(addr + 3000, data, WHB); }
    void printStateHex();
    void printStateDec();
    int getInstrType(int);
    
};

#endif /* Simulator_hpp */
