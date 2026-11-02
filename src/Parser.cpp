#include "Parser.hpp"
#include <cctype>
#include <stdexcept>
#include <cmath>

Parser::Parser(const std::string& input, Environment& env)
        : input(input), pos(0), env(env) {
    functions["max"] = [](const std::vector<double>& args) {
        if (args.size() != 2) throw std::runtime_error("max() takes 2 arguments");
        return std::max(args[0], args[1]);
    };
    functions["min"] = [](const std::vector<double>& args) {
        if (args.size() != 2) throw std::runtime_error("min() takes 2 arguments");
        return std::min(args[0], args[1]);
    };
    functions["pow"] = [](const std::vector<double>& args) {
        if (args.size() != 2) throw std::runtime_error("pow() takes 2 arguments");
        return std::pow(args[0], args[1]);
    };
    functions["abs"] = [](const std::vector<double>& args) {
        if (args.size() != 1) throw std::runtime_error("abs() takes 1 argument");
        return std::abs(args[0]);
    };
}

char Parser::peek() const {
    if (pos >= input.length()) return '\0';
    return input[pos];
}

char Parser::get() {
    if (pos >= input.length()) return '\0';
    return input[pos++];
}

void Parser::skipWhitespace() {
    while (isspace(peek())) get();
}

double Parser::parse() {
    skipWhitespace();

    if (input.substr(pos, 3) == "var") {
        pos += 3;
        skipWhitespace();
        std::string name;
        while (isalnum(peek())) name += get();
        skipWhitespace();
        if (get() != '=') throw std::runtime_error("Expected '=' after variable name");
        skipWhitespace();
        double value = parseExpression();
        env.set(name, value);
        return value;
    } else {
        double result = parseExpression();
        skipWhitespace();
        if (peek() != '\0') throw std::runtime_error("Unexpected input at end");
        return result;
    }
}

double Parser::parseExpression() {
    double left = parseTerm();
    while (true) {
        skipWhitespace();
        char op = peek();
        if (op == '+' || op == '-') {
            get();
            double right = parseTerm();
            if (op == '+') left += right;
            else left -= right;
        } else {
            break;
        }
    }
    return left;
}

double Parser::parseTerm() {
    double left = parseFactor();
    while (true) {
        skipWhitespace();
        char op = peek();
        if (op == '*' || op == '/') {
            get();
            double right = parseFactor();
            if (op == '*') left *= right;
            else if (right == 0) throw std::runtime_error("Division by zero");
            else left /= right;
        } else {
            break;
        }
    }
    return left;
}

double Parser::parseFactor() {
    skipWhitespace();
    if (peek() == '(') {
        get(); // (
        double result = parseExpression();
        skipWhitespace();
        if (get() != ')') throw std::runtime_error("Missing ')'");
        return result;
    } else if (isalpha(peek())) {
        std::string name;
        while (isalnum(peek())) name += get();
        skipWhitespace();
        if (peek() == '(') {
            return parseFunctionCall(name);
        } else if (env.exists(name)) {
            return env.get(name);
        } else {
            throw std::runtime_error("Unknown identifier: " + name);
        }
    } else {
        return parseNumber();
    }
}

double Parser::parseNumber() {
    skipWhitespace();
    std::string number;
    if (peek() == '-') number += get();
    while (isdigit(peek()) || peek() == '.') {
        number += get();
    }
    if (number.empty()) throw std::runtime_error("Expected number");
    return std::stod(number);
}

double Parser::parseFunctionCall(const std::string& name) {
    if (functions.find(name) == functions.end()) {
        throw std::runtime_error("Unknown function: " + name);
    }

    get();
    std::vector<double> args;

    skipWhitespace();
    if (peek() != ')') {
        while (true) {
            args.push_back(parseExpression());
            skipWhitespace();
            if (peek() == ',') {
                get();
                skipWhitespace();
            } else {
                break;
            }
        }
    }

    if (get() != ')') throw std::runtime_error("Expected ')' after function arguments");

    return functions[name](args);
}
