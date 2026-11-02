#include "Environment.hpp"
#include <stdexcept>

void Environment::set(const std::string& name, double value) {
    variables[name] = value;
}

double Environment::get(const std::string& name) const {
    auto it = variables.find(name);
    if (it == variables.end()) throw std::runtime_error("Undefined variable: " + name);
    return it->second;
}

bool Environment::exists(const std::string& name) const {
    return variables.count(name) > 0;
}
