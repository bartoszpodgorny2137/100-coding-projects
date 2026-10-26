#include <iostream>
#include <string>
#include <vector>
#include <map>

enum class JsonType {
    Null,
    Bool,
    Number,
    String,
    Array,
    Object
};
struct JsonValue {
    JsonType type = JsonType::Null;
    bool boolean = false;
    double number = 0.0;
    std::string str = "";
    std::vector<JsonValue> array;
    std::map<std::string, JsonValue> object;
};

int main() {
    JsonValue value;
    value.type = JsonType::Number;
    value.number = 42;
    std::cout <<value.number<< std::endl;
    return 0;
}
