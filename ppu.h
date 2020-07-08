#ifndef _PPU_H_
#define _PPU_H_

#include "memory.h"

class PPU {
public:
    void transfer_to_vram(char value);
    void transfer_to_spram(char value);
    void next();
    void reset();
    PPU(memory *m);
    ~PPU();

private:
    memory *mem;
    memory *vram;
    char spram[256];
};

#endif