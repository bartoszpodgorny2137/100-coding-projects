#include <iostream>
#include <cstdint>
#include <string>
#include <limits>

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

int readInt(int min, int max) {
    int n;
    while (true) {
        std::cin >> n;
        if (std::cin.fail() || n < min || n > max){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<< "Please enter a number ("<<min<<"-"<<max<<"): ";
        }
        else return n;
    }
}

int main() {
    uint8_t flags = 0b00000000;
    std::cout << "=== BITMASK MANAGER CLI ==="<< std::endl;
    while (true) {
        std::cout<<"1. set bit\n2. clear bit\n3. toggle bit\n4. check bit\n5. exit"<<std::endl;
        std::cout<<"flag status: "<<toBinary(flags)<<std::endl;
        std::cout<<"enter your choice ->: ";
        int input = readInt(1, 5);
        if (input == 5) {std::cout<<"Bye!"<<std::endl; break;}
        std::cout<<"Choose bit (0-7): ";
        int bit = readInt(0, 7);
        switch (input) {
            case 1: setBit(flags, bit); break;
            case 2: clearBit(flags, bit); break;
            case 3: toggleBit(flags, bit); break;
            case 4: std::cout<<(checkBit(flags, bit) ? "ON" : "OFF")<<std::endl; break;
        }
    }
}