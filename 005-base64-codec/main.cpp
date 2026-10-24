#include <iostream>
#include <string>

std::string buildAlphabet() {
    std::string alphabet;
    for (int i = 0; i < 26; i++) {
        alphabet.push_back('A' + i);
    }
    for (int i = 0; i < 26; i++) {
        alphabet.push_back('a' + i);
    }
    for (int i = 0; i < 10; i++) {
        alphabet.push_back('0' + i);
    }
    alphabet += "+/";
    return alphabet;
}

std::string encodeBlock(uint8_t b0, uint8_t b1, uint8_t b2, const std::string& alphabet) {
    int v1 = b0 >> 2;
    int v2 = ((b0 & 0b00000011) << 4) | (b1 >> 4);
    int v3 = ((b1 & 0b00001111) << 2) | (b2 >> 6);
    int v4 = b2 & 0b00111111;

    return std::string() + alphabet[v1] + alphabet[v2] + alphabet[v3] + alphabet[v4];
}

std::string encodePartialBlock(uint8_t b0, uint8_t b1, int remaining, const std::string& alphabet) {
    if (remaining == 1) {
        int v1 = b0 >> 2;
        int v2 = ((b0 & 0b00000011) << 4) | (0 >> 4);
        return std::string() + alphabet[v1] + alphabet[v2] + "==";
    } else {
        int v1 = b0 >> 2;
        int v2 = ((b0 & 0b00000011) << 4) | (b1 >> 4);
        int v3 = ((b1 & 0b00001111) << 2) | (0 >> 6);
        return std::string() + alphabet[v1] + alphabet[v2] + alphabet[v3] + "=";
    }
}

std::string encodeText(const std::string& text) {
    std::string alphabet = buildAlphabet();
    std::string result;

    size_t remaining = text.length()  % 3;
    size_t fullLength = text.length() - remaining;

    for (size_t i = 0; i < fullLength; i+=3) {
        uint8_t b0 = text[i];
        uint8_t b1 = text[i+1];
        uint8_t b2 = text[i+2];
        result += encodeBlock(b0, b1, b2, alphabet);
    }
    if (remaining == 1) {
        uint8_t b0 = text[fullLength];
        result += encodePartialBlock(b0, 0, 1, alphabet);
    } else if (remaining == 2) {
        uint8_t b0 = text[fullLength];
        uint8_t b1 = text[fullLength + 1];
        result += encodePartialBlock(b0, b1, 2, alphabet);
    }
    return result;
}


int main() {
    std::cout << encodeText("Hi! Hi!") << std::endl;
}
