#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

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

std::string stringify(const JsonValue& value) {

    switch (value.type) {
        case JsonType::Null:
            return "null";
        case JsonType::Bool:
            return value.boolean ? "true" : "false";
        case JsonType::Number: {
            std::ostringstream oss;
            oss << value.number;
            return oss.str();
        }
        case JsonType::String:
            return '"'+value.str+'"';
    }
    return "";
}


int main() {
    JsonValue value;
    value.type = JsonType::Number;
    value.number = 42;

    JsonValue flag;
    flag.type = JsonType::Bool;
    flag.boolean = true;

    JsonValue str;
    str.type = JsonType::String;
    str.str = "Test Jan 2137";

    JsonValue nothing;
    nothing.type = JsonType::Null;

    std::cout<<stringify(value)<<std::endl;
    std::cout<<stringify(nothing)<<std::endl;
    std::cout<<stringify(flag)<<std::endl;
    std::cout<<stringify(str)<<std::endl;

    return 0;
}
