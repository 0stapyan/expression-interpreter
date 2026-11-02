#include <iostream>
#include <string>
#include "Interpreter.hpp"

int main() {
    Interpreter interpreter;
    std::string line;

    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        try {
            double result = interpreter.evaluate(line);
            std::cout << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        std::cout << "> ";
    }

    return 0;
}
