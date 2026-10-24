#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> splitLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string current;

    for (char c : line) {
        if (c == ',') {
            fields.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

std::vector<std::vector<std::string>> parseCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> table;

    std::string line;
    while (std::getline(file, line)) {
        table.push_back(splitLine(line));
    }
    return table;
}

int main() {
    auto table = parseCSV("data.csv");
    for (const auto& row : table) {
        for (const std::string& field : row) {
            std::cout << "[" << field << "] ";
        }
        std::cout << std::endl;
    }
    return 0;
}
