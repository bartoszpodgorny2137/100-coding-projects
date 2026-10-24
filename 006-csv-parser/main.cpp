#include <iostream>
#include <string>
#include <vector>

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

int main() {
    auto fields = splitLine("Jan,30,Warszawa");
    for (const std::string& f : fields) {
        std::cout << f << std::endl;
    }
    return 0;
}
