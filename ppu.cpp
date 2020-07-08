#include <stdlib.h>
#include "ppu.h"

PPU::PPU(memory *m) {
    mem = m;
    vram = new memory();
}

PPU::~PPU() {
    delete vram;
    vram = NULL;
}