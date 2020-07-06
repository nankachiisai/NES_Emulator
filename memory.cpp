#include "memory.h"

memory::memory() {
    for (int i = 0;i < 0xffff; i++) {
        array[i] = 0x00;
    }
}

char memory::getByte(unsigned short address) {
    return array[address];
}

void memory::setByte(unsigned short address, unsigned char data) {
    array[address] = data;
}
