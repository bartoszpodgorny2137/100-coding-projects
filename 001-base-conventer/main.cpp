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

int main() {
    std::cout<<decToBin(27);
}