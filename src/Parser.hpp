#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include "Environment.hpp"

class Parser {
public:
    Parser(const std::string& input, Environment& env);
    double parse();

private:
    std::string input;
    size_t pos;
    Environment& env;

    std::unordered_map<std::string, std::function<double(std::vector<double>)>> functions;

    char peek() const;
    char get();

    void skipWhitespace();
    double parseExpression();
    double parseTerm();
    double parseFactor();
    double parseNumber();

    double parseFunctionCall(const std::string& name);
};
