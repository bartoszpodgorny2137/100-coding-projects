#include  <iostream>
#include  <string>

long long decToBin(int dec) {
    long long bin = 0;
    long long weight = 1;
    while (dec > 0) {
        bin += (dec % 2) * weight;
        weight *= 10;
        dec /= 2;
    }
    return bin;
}

long long binToDec(long long bin) {
    long long dec = 0;
    int weight = 1;
    while (bin > 0) {
        dec += (bin % 10) * weight;
        weight *= 2;
        bin /= 10;
    }
    return dec;
}

long long octToBin(int oct) {
    long long weight = 1;
    long long bin = 0;
    while (oct > 0) {
        int cipher = oct % 10;
        int cipherBin = 0;
        int cipherWeight = 1;
        while (cipher > 0) {
            cipherBin += (cipher % 2) * cipherWeight;
            cipherWeight *= 10;
            cipher /= 2;
        }
        bin += cipherBin * weight;
        weight *= 1000;
        oct /= 10;
    }
    return bin;
}

long long binToOct(long long bin) {
    int weight = 1;
    long long oct = 0;
    while (bin > 0) {
        long long cipherBin = bin % 1000;
        long long cipher = 0;
        int cipherWeight = 1;
        while (cipherBin > 0) {
            cipher += (cipherBin % 10) * cipherWeight;
            cipherWeight *= 2;
            cipherBin /= 10;
        }
        oct += cipher * weight;
        weight *= 10;
        bin /= 1000;
    }
    return oct;
}

long long hexToBin(std::string hex) {
    char HexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    long long bin = 0;
    long long weight = 1;
    for (int l = hex.length() - 1; l >= 0; l--) {
        char c = hex[l];
        int value = 0;
        for (int i = 0; i < 16; i++) {
            if (HexChars[i] == c) {
                value = i;
                break;
            }
        }
        int binPack = 0;
        int binWeight = 1;
        while (value > 0) {
            binPack += (value % 2) * binWeight;
            binWeight *= 10;
            value /= 2;
        }
        bin += binPack * weight;
        weight *= 10000;
    }
    return bin;
}

std::string binToHex(long long bin) {
    char HexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::string hex = "";
    long long weight = 1;

    if (bin == 0) return "0";

    while (bin > 0) {
        long long cipherBin = bin % 10000;
        long long cipher = 0;
        int cipherWeight = 1;
        while (cipherBin > 0) {
            cipher += (cipherBin % 10) * cipherWeight;
            cipherWeight *= 2;
            cipherBin /= 10;
        }
        hex = HexChars[cipher] + hex;
        bin /= 10000;
    }
    return hex;
}

int main() {
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
        case 1: {
            binBase = decToBin(std::stoi(inputNumber));
            break;
        }
        case 2: {
            binBase = octToBin(std::stoi(inputNumber));
            break;
        }
        case 3: {
            binBase = std::stoll(inputNumber);
            break;
        }
        case 4: {
            binBase = hexToBin(inputNumber);
            break;
        }
        default: {
            std::cout<<"Invalid number!"<<std::endl;
            return 1;
        }
    }


    std::cout<<"Result: ";
    switch (targetChoice) {
        case 1: {
            std::cout<<binToDec(binBase)<<std::endl;
            break;
        }
        case 2: {
            std::cout<<binToOct(binBase)<<std::endl;
            break;
        }
        case 3: {
            std::cout<<binBase<<std::endl;
            break;
        }
        case 4: {
            std::cout<<binToHex(binBase)<<std::endl;
            break;
        }
        default: {
            std::cout<<"Invalid number!"<<std::endl;
            return 1;
        }
    }
    return 0;
}