#include <iostream>
#include <string>

int main() {
    std::string text = "HELLO"; // Initial text

    // Define the ASCII art characters for each letter
    std::string letterH =
        "H   H\n"
        "H   H\n"
        "HHHHH\n"
        "H   H\n"
        "H   H\n";
    
    std::string letterE =
        "EEEEE\n"
        "E    \n"
        "EEEEE\n"
        "E    \n"
        "EEEEE\n";
    
    std::string letterL =
        "L    \n"
        "L    \n"
        "L    \n"
        "L    \n"
        "LLLLL\n";
    
    std::string letterO =
        " OOO \n"
        "O   O\n"
        "O   O\n"
        "O   O\n"
        " OOO \n";

    // Display the initial 3D text
    std::cout << "Current Text:\n";
    for (char c : text) {
        switch (c) {
            case 'H':
                std::cout << letterH;
                break;
            case 'E':
                std::cout << letterE;
                break;
            case 'L':
                std::cout << letterL;
                break;
            case 'O':
                std::cout << letterO;
                break;
            default:
                std::cout << "    \n"
                          << "    \n"
                          << "    \n"
                          << "    \n"
                          << "    \n";
                break;
        }
    }

    return 0;
}
