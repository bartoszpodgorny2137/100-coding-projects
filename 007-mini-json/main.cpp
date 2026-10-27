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
        case JsonType::Null: return "null";
        case JsonType::Bool: return value.boolean ? "true" : "false";
        case JsonType::Number: {
            std::ostringstream oss;
            oss << value.number;
            return oss.str();
        }
        case JsonType::String: return '"'+value.str+'"';
        case JsonType::Array: {
            std::string result = "[";
            for (size_t i=0; i<value.array.size(); i++){
                if ( i> 0) {
                    result += ",";
                }
                result += stringify(value.array.at(i));
            }
            result += "]";
            return result;
        }
        case JsonType::Object: {
            std::string result = "{";
            bool first = true;
            for (const auto& pair : value.object) {
                if (!first) {
                    result += ",";
                }
                first = false;
                result += '"'+pair.first+'"'+':'+stringify(pair.second);
            }
            result += "}";
            return result;
        }
    }
    return "";
}

void skipWhitespace(const std::string& text, size_t& pos) {
    while (pos < text.length() &&
        (text[pos] == ' ' || text[pos] == '\t' || text[pos] == '\r' || text[pos] == '\n')
        ) {
        pos++;
    }
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

    JsonValue array;
    array.type = JsonType::Array;
    for (int n = 1; n <= 4; n++) {
        JsonValue item;
        item.type = JsonType::Number;
        item.number = n;
        array.array.push_back(item);
    }

    JsonValue object;
    object.type = JsonType::Object;
    object.object["age"] = value;
    object.object["name"] = str;

    std::cout<<stringify(value)<<std::endl;
    std::cout<<stringify(nothing)<<std::endl;
    std::cout<<stringify(flag)<<std::endl;
    std::cout<<stringify(str)<<std::endl;
    std::cout<<stringify(array)<<std::endl;
    std::cout <<stringify(object)<< std::endl;

    std::string text = "   [1]";
    size_t pos = 0;
    skipWhitespace(text, pos);
    std::cout << pos << std::endl;

    return 0;
}
