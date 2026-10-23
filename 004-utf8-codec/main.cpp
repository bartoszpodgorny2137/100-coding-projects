#include <iostream>
#include <vector>
#include <cstdint>

std::vector<uint8_t> encode(uint32_t cp) {
    std::vector<uint8_t> bytes;

    if (cp <= 127) {
        bytes.push_back(cp);
        return bytes;
    } else if (cp <= 2047) {
        uint8_t first = (cp >> 6) | 0b11000000;
        bytes.push_back(first);

        uint8_t second = (cp & 0b00111111)| 0b10000000;
        bytes.push_back(second);

        return bytes;
    } else if (cp <= 65535) {
        uint8_t first = (cp >> 12) | 0b11100000;
        bytes.push_back(first);

        uint8_t second = ((cp >> 6) & 0b00111111)| 0b10000000;
        bytes.push_back(second);

        uint8_t third = (cp & 0b00111111) | 0b10000000;
        bytes.push_back(third);

        return bytes;
    } else {
        uint8_t first = (cp >> 18) | 0b11110000;
        bytes.push_back(first);

        uint8_t second = ((cp >> 12) & 0b00111111) | 0b10000000;
        bytes.push_back(second);

        uint8_t third = ((cp >> 6) & 0b00111111)| 0b10000000;
        bytes.push_back(third);

        uint8_t fourth = (cp & 0b00111111) | 0b10000000;
        bytes.push_back(fourth);

        return bytes;
    }
}

uint32_t decode(const std::vector<uint8_t>& bytes) {
    uint32_t result = 0;
    if ((bytes[0] >> 7) == 0b0) {
        return bytes[0];
    }else if ((bytes[0] >> 5) == 0b110) {
        result = ((bytes[0] & 0b00011111) << 6) | (bytes[1] & 0b00111111);
        return result;
    } else if ((bytes[0] >> 4) == 0b1110) {
        result = ((bytes[0] & 0b00001111) << 12) | ((bytes[1] & 0b00111111) << 6) | (bytes[2] & 0b00111111);
        return result;
    } else if ((bytes[0] >> 3) == 0b11110) {
        result = ((bytes[0] & 0b00000111) << 18 | ((bytes[1] & 0b00111111) << 12) | ((bytes[2] & 0b00111111) << 6) | (bytes[3] & 0b00111111));
        return result;
    }
    return 0;
}

int main() {
    auto bytes = encode(128512);
    for (uint8_t byte : bytes) {
        std::cout << static_cast<int>(byte) << " ";
    }
}
