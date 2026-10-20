#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <limits>

using AsciiTable = std::array<char, 128>;

void placeString(AsciiTable& table, int start, const std::string&s) {
    for (int i = 0; i < s.length(); ++i) {
        table[start + i] = s[i];
    }
}

void placeSequence(AsciiTable& table, int start, char c, int n) {
    for (int i = 0; i < n; ++i) {
        table[start + i] = c + i;
    }
}

AsciiTable buildTable() {
    AsciiTable table{};
    std::string symbolsBeforeDigits = " !\"#$%&'()*+,-./";
    std::string symbolsBeforeUppers = ":;<=>?@";
    std::string symbolsBeforeLowers =  "[\\]^_`";
    std::string symbolsAfterLowers = "{|}~";

    placeString(table, 32, symbolsBeforeDigits);
    placeSequence(table, 48, '0', 10);
    placeString(table, 58, symbolsBeforeUppers);
    placeSequence(table, 65, 'A', 26);
    placeString(table, 91, symbolsBeforeLowers);
    placeSequence(table, 97, 'a', 26);
    placeString(table, 123, symbolsAfterLowers);

    return table;
}

int encodeChar(const AsciiTable& table, char c) {
    for (int i = 32; i < 127; i++) {
        if (table[i] == c) return i;
    }
    return -1;
}

char decodeChar(const AsciiTable& table, int n) {
    if (n >= 32 && n < 127) return table[n];
    return '?';
}

std::string decodeText(const AsciiTable& table, const std::string&s) {
    std::string result;
    std::istringstream stream(s);
    int n;
    while (stream >> n) {
        result += decodeChar(table, n);
    }
    return result;
}

std::string encodeText(const AsciiTable& table, const std::string& s) {
    std::string result;
    for (int i = 0; i < s.length(); ++i) {
        int code = encodeChar(table, s[i]);
        result += (code == -1) ? "? " : std::to_string(code) + " ";
    }
    return result;
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

int main(){
    const AsciiTable table = buildTable();
    bool isTrue = true;
    while (isTrue) {
        std::cout << "Ascii Encoder/Decoder CLI" << std::endl;
        std::cout << "1. Encode \n2. Decode \n3. Table\n 4. Exit" << std::endl;
        std::string input;
        std::cout<< "->: ";
        int choice = readInt(1, 4);
        switch (choice) {
            case 1: {
                std::cout<<"Enter text to encode: ";
                std::getline(std::cin,input);
                std::cout<<"Encoded code: "<<encodeText(table, input)<<std::endl;
                break;
            }
            case 2: {
                std::cout<<"Enter code to decode: ";
                std::getline(std::cin,input);
                std::cout<<"Decoded text: "<<decodeText(table, input)<<std::endl;
                break;
            }
            case 3: {
                std::cout<<"ASCII Table"<<std::endl;
                for (int i = 32; i < 127; i++) {
                    std::cout<< i << " : " << table[i] << std::endl;
                }
                break;
            }
            case 4: {
                std::cout<<"Exiting..."<<std::endl;
                isTrue = false;
                break;
            }
        }
    }
}
