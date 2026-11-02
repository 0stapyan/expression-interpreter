#pragma once
#include <string>
#include "Environment.hpp"

class Interpreter {
public:
    double evaluate(const std::string& input);

private:
    Environment env;
};
