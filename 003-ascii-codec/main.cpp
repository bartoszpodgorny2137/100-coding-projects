#include <iostream>
#include <array>
#include <string>


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

int main(){
    const AsciiTable table = buildTable();
    for (int i = 32; i < 127; i++) {
        std::cout<< i << " : " << table[i] << std::endl;
    }
}
