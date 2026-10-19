#include <iostream>
#include <cstdint>
#include <string>
#include <limits>
#include <array>

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
            std::cout<< "Please enter a number ("<<min<<"-"<<max<<") ->: ";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return n;
        }
    }
}

std::string readName(int n){
    std::string s;
    while (true) {
        std::cout<<"Enter a name for "<<n<<" flag ->: ";
        std::getline(std::cin, s);
        if (s.empty()) std::cout<< "Invalid name for flag "<<n<<std::endl;
        else return s;
    }
}

int main() {
    uint8_t flags = 0b00000000;
    std::array<std::string, 8> names;
    for (int i=0; i<8; i++) {
        names[i] = "flag" + std::to_string(i);
    }
    while (true) {
        std::cout << "=== BITMASK MANAGER CLI ==="<< std::endl;
        std::cout<<" Flag status: "<<toBinary(flags)<<std::endl;
        for (int i=0; i<8; i++) {
            std::cout<<"  ["<<i<<"] "<<names[i]<<": "
            <<(checkBit(flags, i) ? "ON" : "OFF")<<std::endl;
        }
        std::cout<<
            " 1 - set bit | 2 - clear bit | 3 - toggle bit | 4 - rename bit | 5 - exit"
        <<std::endl;
        std::cout<<"Enter your choice ->: ";
        int input = readInt(1, 5);
        if (input == 5) {std::cout<<"Bye!"<<std::endl; break;}
        std::cout<<"Choose bit (0-7) ->: ";
        int bit = readInt(0, 7);
        switch (input) {
            case 1: setBit(flags, bit); break;
            case 2: clearBit(flags, bit); break;
            case 3: toggleBit(flags, bit); break;
            case 4: names[bit] = readName(bit); break;
        }
    }
}