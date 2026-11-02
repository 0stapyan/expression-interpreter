#include "Interpreter.hpp"
#include "Parser.hpp"
#include <stdexcept>

double Interpreter::evaluate(const std::string& input) {
    Parser parser(input, env);
    return parser.parse();
}
