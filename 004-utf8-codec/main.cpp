#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <string>
#include <sstream>

int howManyBytes(uint8_t firstByte) {
    if ((firstByte >> 7) == 0b0) {
        return 1;
    } else if ((firstByte >> 5) == 0b110) {
        return 2;
    } else if ((firstByte >> 4) == 0b1110) {
        return 3;
    } else if ((firstByte >> 3) == 0b11110) {
        return 4;
    }
    return 0;
}

std::string byteToHex(uint8_t byte) {
    const char* hexDigits = "0123456789ABCDEF";

    uint8_t high = byte >> 4;
    uint8_t low  = byte & 0b00001111;

    std::string result;
    result += hexDigits[high];
    result += hexDigits[low];
    return result;
}

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
    int numberOfBytes = howManyBytes(bytes[0]);
    if (numberOfBytes == 1) {
        return bytes[0];
    }else if (numberOfBytes == 2) {
        result = ((bytes[0] & 0b00011111) << 6) | (bytes[1] & 0b00111111);
        return result;
    } else if (numberOfBytes == 3) {
        result = ((bytes[0] & 0b00001111) << 12) | ((bytes[1] & 0b00111111) << 6) | (bytes[2] & 0b00111111);
        return result;
    } else if (numberOfBytes == 4) {
        result = ((bytes[0] & 0b00000111) << 18 | ((bytes[1] & 0b00111111) << 12) | ((bytes[2] & 0b00111111) << 6) | (bytes[3] & 0b00111111));
        return result;
    }
    return 0;
}

void analyzeText(const std::string& text) {
    size_t i = 0;
    while (i < text.length()) {
        uint8_t firstByte = static_cast<uint8_t>(text[i]);
        int n = howManyBytes(firstByte);

        std::vector<uint8_t> charBytes;
        for (int k =0; k < n; k++) {
            charBytes.push_back(static_cast<uint8_t>(text[i + k]));
        }
        uint32_t cp = decode(charBytes);
        std::cout << "U+"<<cp<< " bytes:";
        for (uint8_t k : charBytes) std::cout<<" "<< byteToHex(k);
        ;std::cout<<std::endl;

        i += n;
    }
}

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

int main() {
    std::cout<<"UTF-8 Codec CLI"<<std::endl;
    bool running = true;
    while (running) {
        std::cout<<"1. Encode\n2. Decode\n3. Analyze Text\n4. Exit "<<std::endl;
        std::cout<<"Enter input: ";
        int choice = readInt(1, 4);
        switch(choice) {
            case 1: {
                std::cout<<"Enter code point (decimal): ";
                int cp = readInt(0, 1114111);
                auto bytes = encode(static_cast<uint32_t>(cp));

                std::cout<< "UTF-8 bytes";
                for (uint8_t b : bytes) {
                    std::cout<<" "<<byteToHex(b);
                }
                std::cout<<std::endl;
                break;
            }
            case 2: {
                std::cout << "Enter UTF-8 bytes: (decimal, space-separated): ";
                std::string line;
                std::getline(std::cin, line);

                std::istringstream stream(line);
                std::vector<uint8_t> bytes;
                int b;
                while (stream >> b) {
                    bytes.push_back(static_cast<uint8_t>(b));
                }
                if (bytes.empty()) {
                    std::cout << "No bytes entered!" << std::endl;
                    break;
                }
                uint32_t cp = decode(bytes);
                std::cout<< "Code point: U+"<< cp << " ("<<cp<<")"<<std::endl;
                break;
            }
            case 3: {
                std::cout<<"Enter text: ";
                std::string text;
                std::getline(std::cin, text);
                analyzeText(text);
                break;
            }
            case 4: {
                std::cout<<"Exiting..."<<std::endl;
                running = false;
                break;
            }
        }
    }
}
