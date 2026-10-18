#include <iostream>
#include <cstdint>
#include <string>

std::string toBinary(uint8_t f) {
    std::string s = "";
    for (int i=7; i>-1; i--){s += (f & (1 << i)) ? '1' : '0';}
    return s;
}

void setBit(uint8_t& f, int n) {
    f |= 1 << n;
}

void clearBit(uint8_t& f, int n) {
    f &= ~(1 << n);
}

void toggleBit(uint8_t& f, int n) {
    f ^= 1 << n;
}

bool checkBit(uint8_t f, int n) {
    return (f & (1 << n));
}


int main() {
    uint8_t flags = 0b00000000;
    setBit(flags, 7);
    clearBit(flags, 3);
    toggleBit(flags, 4);
    std::cout<<checkBit(flags, 7)<<std::endl;
    std::cout << toBinary(flags)<< std::endl;

    /*
     *1. set bit
     *2. clear bit
     *3. toogle bit
     *4. check bit
     *5. exit
     *
     */

}