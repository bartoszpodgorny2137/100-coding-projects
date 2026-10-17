#include  <iostream>
#include  <string>

int decToBin(int dec) {
    int bin = 0;
    int weight = 1;
    while (dec > 0) {
        bin += (dec % 2) * weight;
        weight *= 10;
        dec /= 2;
    }
    return bin;
}

int binToDec(int bin) {
    int dec = 0;
    int weight = 1;
    while (bin > 0) {
        dec += (bin % 10) * weight;
        weight *= 2;
        bin /= 10;
    }
    return dec;
}

int octToBin(int oct) {
    int weight = 1;
    int bin = 0;
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

int binToOct(int bin) {
    int weight = 1;
    int oct = 0;
    while (bin > 0) {
        int cipherBin = bin % 1000;
        int cipher = 0;
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
        int cipherBin = bin % 10000;
        int cipher = 0;
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
    //std::cout<<decToBin(27);
    //std::cout<<binToDec(11000000)<<std::endl;
    //std::cout<<octToBin(12);
    //std::cout<<binToOct(1010)<<std::endl;
    //std::cout<<hexToBin("3B");
    std::cout<<binToHex(110010111010)<<std::endl;
}