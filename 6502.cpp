#include "6502.h"
#include "memory.h"

CPU_6502::CPU_6502(memory *m) {
    mem = m;

    pc = (mem->getByte(0x00fd) << 8) | (mem->getByte(0xfffc));
    a = 0x00;
    x = 0x00;
    y = 0x00;
    sp = 0x00;
    p = 0x20 | STATUS_I;
    count = 0;
    res = 1;
}

void CPU_6502::next() {
    // reset
    if (res != 0) {
        res++;
        return;
    }
    if (res == 7) {
        res = 0;
        return;
    }

    // Instruction Fetch & Execution
    if (count == 0) {
        unsigned char opcode = mem->getByte(pc);
        char operandA;
        char tmp;

        switch (opcode) {
        // Immediate ADC
        case 0x69:
            count = 1;

            operandA =  (char) mem->getByte(pc + 1);

            if (check_overflow(a, operandA)) SET(p, STATUS_V);
            else CLEAR(p, STATUS_V);

            if (check_carry(a, operandA)) SET(p, STATUS_C);
            else CLEAR(p, STATUS_C);

            a += operandA;
            pc += 2;

            if (check_negative(a)) SET(p, STATUS_N);
            else CLEAR(p, STATUS_N);

            if (check_zero(a)) SET(p, STATUS_Z);
            else CLEAR(p, STATUS_Z);

            break;

        // Zero Page ADC
        case 0x65:
            break;
        
        // Zero Page,X ADC
        case 0x75:
            break;
        
        // Implied SEI
        case 0x78:
            count = 1;

            SET(p, STATUS_I);
            pc++;

            break;

        // Immediate LDX
        case 0xa2:
            count = 1;

            x = mem->getByte(pc + 1);
            pc += 2;

            if (check_negative(x)) SET(p, STATUS_N);
            else CLEAR(p, STATUS_N);

            if (check_zero(x)) SET(p, STATUS_Z);
            else CLEAR(p, STATUS_Z);

            break;

        // Implied TXS
        case 0x9a:
            count = 1;

            sp = x;
            pc++;

            break;

        // Immediate LDA
        case 0xa9:
            count = 1;

            a = mem->getByte(pc + 1);
            pc += 2;

            if (check_negative(x)) SET(p, STATUS_N);
            else CLEAR(p, STATUS_N);

            if (check_zero(x)) SET(p, STATUS_Z);
            else CLEAR(p, STATUS_Z);

            break;

        // Absolute STA
        case 0x9d:
            count = 3;

            mem->setByte(((unsigned short) mem->getByte(pc + 1) << 8) |
                          (unsigned short) mem->getByte(pc + 2), a);
            pc += 3;

            break;
        }
    }
    else count--;
}

int CPU_6502::check_negative(char s) {
    if (s < 0) return 1;
    else return 0;
}

int CPU_6502::check_overflow(char s, char t) {
    if ((s > 0) && ((unsigned char) (s + t) > 0x7f)) return 1;
    else if ((s < 0) && ((unsigned char) (s + t) < 0x80)) return 1;
    else return 0;
}

int CPU_6502::check_zero(char s) {
    if (s == 0) return 1;
    else return 0;
}

int CPU_6502::check_carry(char s, char t) {
    if ((short) (s + t) >= 0x100) return 1;
    else return 0;
}
