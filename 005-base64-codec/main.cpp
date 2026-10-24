#include <iostream>
#include <string>
#include <vector>

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

std::vector<uint8_t> decodeBlock(char c1, char c2, char c3, char c4, const std::string& alphabet) {
    std::vector<uint8_t> result;
    int v1 = alphabet.find(c1);
    int v2 = alphabet.find(c2);
    int v3 = alphabet.find(c3);
    int v4 = alphabet.find(c4);
    uint8_t b0 = (v1 << 2) | (v2 >> 4);
    uint8_t b1 = ((v2 & 0b00001111) << 4) | (v3 >> 2);
    uint8_t b2 = ((v3 & 0b00000011) << 6) | v4;
    result.push_back(b0);
    result.push_back(b1);
    result.push_back(b2);
    return result;

}

std::string decodeText(const std::string& encoded) {
    std::string alphabet = buildAlphabet();
    std::vector<uint8_t> bytes;

    for (size_t i = 0; i < encoded.length(); i += 4) {
        char c1 = encoded[i];
        char c2 = encoded[i+1];
        char c3 = encoded[i+2];
        char c4 = encoded[i+3];

        auto block = decodeBlock(c1, c2, c3, c4, alphabet);

        int padding = 0;
        if (c3 == '=') padding = 2;
        else if (c4 == '=') padding = 1;

        for (size_t k = 0; k < 3 - padding; k++) {
            bytes.push_back(block[k]);
        }
    }

    return std::string(bytes.begin(), bytes.end());
}

int main() {
    std::cout << "Base64 Codec CLI" << std::endl;
    bool running = true;
    while (running) {
        std::cout << "1. Encode\n2. Decode\n3. Exit" << std::endl;
        std::cout << "Enter input: ";
        int choice = readInt(1, 3);
        switch (choice) {
            case 1: {
                std::cout << "Enter text to encode: ";
                std::string text;
                std::getline(std::cin, text);
                std::cout << "Encoded: " << encodeText(text) << std::endl;
                break;
            }
            case 2: {
                std::cout << "Enter Base64 to decode: ";
                std::string text;
                std::getline(std::cin, text);
                std::cout << "Decoded: " << decodeText(text) << std::endl;
                break;
            }
            case 3: {
                std::cout << "Exiting..." << std::endl;
                running = false;
                break;
            }
        }
    }
}
