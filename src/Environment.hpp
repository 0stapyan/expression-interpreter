#pragma once
#include <string>
#include <unordered_map>

class Environment {
public:
    void set(const std::string& name, double value);
    double get(const std::string& name) const;
    bool exists(const std::string& name) const;

private:
    std::unordered_map<std::string, double> variables;
};
