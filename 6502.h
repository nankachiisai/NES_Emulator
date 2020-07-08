#ifndef _6502_H_
#define _6502_H_

#include "memory.h"

#define STATUS_C 0x01
#define STATUS_Z 0x02
#define STATUS_I 0x04
#define STATUS_D 0x08
#define STATUS_B 0x10
#define STATUS_V 0x40
#define STATUS_N 0x80

#define SET(P, N) P |= N
#define CLEAR(P, N) P &= N
#define ADDR(hword, lword) ((unsigned short) hword << 8) |\
                           (unsigned short) lword

enum interrupt {
    NMI,
    IRQ,
    BRK
};

class CPU_6502 {
public:
    void next();
    void reset();
    void interrupt(enum interrupt i);
    CPU_6502(memory *m);

private:
    unsigned short pc; // Program Counter
    char a;            // Accumulator
    char x;            // Index Register X
    char y;            // Index Register Y
    char sp;           // Stack Pointer
    char p;            // Status Register
    memory *mem;
    int count;
    int res;

    int check_negative(char s);
    int check_overflow(char s, char t);
    int check_zero(char s);
    int check_carry(char s, char t);
};

#endif