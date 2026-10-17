#include  <iostream>

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

int main() {
    //std::cout<<decToBin(27);
    std::cout<<binToDec(11000000)<<std::endl;
}