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
    std::cout << "Welcome to bitmask manager CLI"<< std::endl;
    while (true) {
        std::cout<<"1. set bit\n2. clear bit\n3. toggle bit\n4. check bit\n5. exit"<<std::endl;
        std::cout<<"flag status: "<<toBinary(flags)<<std::endl;
        std::cout<<"enter your choice ->: ";
        int input;
        std::cin >> input;
        if (input == 5) {std::cout<<"Bye!"<<std::endl; break;}
        if (input <= 0 || input >= 5) {std::cout<<"Invalid number!"<<std::endl; continue;}
        std::cout<<"Choose bit (0-7): ";
        int bit;
        std::cin >> bit;
        if (bit <0 || bit > 7) { std::cout<<"Invalid bit!!!"<<std::endl ; continue; }
        switch (input) {
            case 1: setBit(flags, bit); break;
            case 2: clearBit(flags, bit); break;
            case 3: toggleBit(flags, bit); break;
            case 4: std::cout<<(checkBit(flags, bit) ? "ON" : "OFF")<<std::endl; break;
        }
    }
}