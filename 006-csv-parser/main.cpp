#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> splitLine(const std::string& line) {
    bool insideQuotes = false;
    std::vector<std::string> fields;
    std::string current;

    for (size_t i = 0; i< line.length(); i++){
        char c = line[i];
        if (c == '"') {
            if (insideQuotes  && i +1 < line.length() && line[i+1] == '"' ) {
                current += '"';
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        }
        else if (c == ',' && !insideQuotes) {
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
