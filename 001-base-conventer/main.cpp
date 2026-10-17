#include  <iostream>
#include  <string>

long long decToBin(int dec) {
    return dec;
}

long long binToDec(long long bin) {
    return bin;
}

long long octToBin(int oct) {
    long long bin = 0;
    int shift = 0;
    while (oct > 0) {
        long long cipher = oct % 10;
        bin |= (cipher << shift);
        shift += 3;
        oct /= 10;
    }
    return bin;
}

long long binToOct(long long bin) {
    long long oct = 0;
    long long weight = 1;
    while (bin > 0) {
        oct += (bin & 7) * weight;
        weight *= 10;
        bin >>= 3;
    }
    return oct;
}

long long hexToBin(std::string hex) {
    long long bin = 0;
    for (char c : hex) {
        int value = 0;
        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'F') value = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') value = c - 'a' + 10;

        bin = (bin << 4) | value;
    }
    return bin;
}

std::string binToHex(long long bin) {
    if (bin == 0) return "0";
    char HexChars[] = "0123456789ABCDEF";
    std::string hex = "";
    while (bin > 0) {
        hex = HexChars[bin & 15] + hex;
        bin >>= 4;
    }
    return hex;
}

int main() {
    while (true) {
        std::cout << "Base Systems Calculator - (bin/dec/oct/hex)" << std::endl;
        std::cout<<"1 - Decimal\n2 - Octal\n3 - Binary\n4 - Hexagonal"<<std::endl;

        std::cout<<"Select the numeral system for your number: ";
        int sourceChoice;
        std::cin>>sourceChoice;

        std::cout<<"Enter your number: ";
        std::string inputNumber;
        std::cin>>inputNumber;

        std::cout<<"Select the target numeral system: ";
        int targetChoice;
        std::cin>>targetChoice;

        long long binBase = 0;

        switch(sourceChoice) {
            case 1: binBase = decToBin(std::stoi(inputNumber)); break;
            case 2: binBase = octToBin(std::stoi(inputNumber)); break;
            case 3: binBase = std::stoll(inputNumber, nullptr, 2); break;
            case 4: binBase = hexToBin(inputNumber); break;
            default: std::cout<<"Invalid number!"<<std::endl; return 1;
        }

        std::cout<<"Result: ";
        switch (targetChoice) {
            case 1: std::cout<<binToDec(binBase)<<std::endl; break;
            case 2: std::cout<<binToOct(binBase)<<std::endl; break;
            case 3: {
                if (binBase == 0) {std::cout<<0;}
                std::string s = "";
                long long temp = binBase;
                while (temp > 0) {
                    s = (temp & 1 ? "1" : "0") + s;
                    temp >>= 1;
                }
                std::cout<<s<<std::endl; break;
            }
            case 4: std::cout<<binToHex(binBase)<<std::endl; break;
            default: std::cout<<"Invalid number!"<<std::endl; return 1;
        }
        std::cout<<"Continue? (y/n) ";
        std::string continueChoice;
        std::cin>>continueChoice;
        if (continueChoice == "n") {
            break;
        }
    }
    return 0;
}