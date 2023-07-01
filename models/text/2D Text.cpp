#include <iostream>
#include <string>

int main() {
    std::string text = "Hello, World!"; // Initial text

    // Display the initial text
    std::cout << "Current Text: " << text << std::endl;

    // Prompt the user for new text
    std::cout << "Enter new text: ";
    std::getline(std::cin, text);

    // Display the updated text
    std::cout << "Updated Text: " << text << std::endl;

    return 0;
}
