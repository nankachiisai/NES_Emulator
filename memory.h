#ifndef _MEMORY_H_
#define _MEMORY_H_

class memory {
public:
    memory();
    char getByte(unsigned short address);
    void setByte(unsigned short address, unsigned char data);

private:
    unsigned char array[0xffff];
};

#endif