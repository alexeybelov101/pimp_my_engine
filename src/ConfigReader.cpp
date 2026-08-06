#include "ConfigReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

bool ConfigReader::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line[0] == '#' || line[0] == ';') {
            continue;
        }

        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) {
            continue;
        }

        std::string key = trim(line.substr(0, eq_pos));
        std::string value = trim(line.substr(eq_pos + 1));

        if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
            value = value.substr(1, value.size() - 2);
        }

        values[key] = value;
    }
    return true;
}

std::string ConfigReader::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> ConfigReader::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        std::string trimmed = trim(token);
        if (!trimmed.empty()) {
            tokens.push_back(trimmed);
        }
    }
    return tokens;
}

std::string ConfigReader::get_string(const std::string& key) const {
    auto it = values.find(key);
    if (it == values.end()) {
        throw std::runtime_error("Config key not found: " + key);
    }
    return it->second;
}

std::optional<std::string> ConfigReader::get_string_opt(const std::string& key) const {
    auto it = values.find(key);
    if (it == values.end()) {
        return std::nullopt;
    }
    return it->second;
}

double ConfigReader::get_double(const std::string& key) const {
    std::string str = get_string(key);
    try {
        double value = std::stod(str);
        validate_positive(key, value);
        return value;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse double for key: " + key +
                                " value: " + str + " error: " + e.what());
    }
}

std::optional<double> ConfigReader::get_double_opt(const std::string& key) const {
    auto opt = get_string_opt(key);
    if (!opt.has_value()) {
        return std::nullopt;
    }
    try {
        double value = std::stod(opt.value());
        validate_positive(key, value);
        return value;
    } catch (...) {
        return std::nullopt;
    }
}

int ConfigReader::get_int(const std::string& key) const {
    std::string str = get_string(key);
    try {
        int value = std::stoi(str);
        if (value < 0) {
            throw std::runtime_error("Negative value for " + key);
        }
        return value;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse int for key: " + key +
                                " value: " + str + " error: " + e.what());
    }
}

std::optional<int> ConfigReader::get_int_opt(const std::string& key) const {
    auto opt = get_string_opt(key);
    if (!opt.has_value()) {
        return std::nullopt;
    }
    try {
        return std::stoi(opt.value());
    } catch (...) {
        return std::nullopt;
    }
}

bool ConfigReader::get_bool(const std::string& key) const {
    std::string str = get_string(key);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str == "true" || str == "1" || str == "yes" || str == "on") return true;
    if (str == "false" || str == "0" || str == "no" || str == "off") return false;
    throw std::runtime_error("Failed to parse bool for key: " + key + " value: " + str);
}

std::vector<double> ConfigReader::get_double_array(const std::string& key) const {
    std::vector<double> result;
    auto it = values.find(key);
    if (it == values.end()) {
        return result;
    }

    std::vector<std::string> tokens = split(it->second, ',');
    for (const auto& token : tokens) {
        try {
            double value = std::stod(token);
            result.push_back(value);
        } catch (...) {
            throw std::runtime_error("Failed to parse double array for key: " +
                                    key + " token: " + token);
        }
    }
    return result;
}

std::vector<int> ConfigReader::get_int_array(const std::string& key) const {
    std::vector<int> result;
    auto it = values.find(key);
    if (it == values.end()) {
        return result;
    }

    std::vector<std::string> tokens = split(it->second, ',');
    for (const auto& token : tokens) {
        try {
            result.push_back(std::stoi(token));
        } catch (...) {
            throw std::runtime_error("Failed to parse int array for key: " +
                                    key + " token: " + token);
        }
    }
    return result;
}

bool ConfigReader::has_key(const std::string& key) const {
    return values.find(key) != values.end();
}

void ConfigReader::print_all() const {
    std::cout << "=== Config Contents ===" << std::endl;
    for (const auto& [key, value] : values) {
        std::cout << key << " = " << value << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

void ConfigReader::validate_positive(const std::string& key, double value) const {
    if (value <= 0) {
        throw std::runtime_error("Value must be positive for key: " + key +
                                " got: " + std::to_string(value));
    }
}

void ConfigReader::validate_range(const std::string& key, double value,
                                  double min, double max) const {
    if (value < min || value > max) {
        throw std::runtime_error("Value out of range for key: " + key +
                                " got: " + std::to_string(value) +
                                " expected: [" + std::to_string(min) +
                                ", " + std::to_string(max) + "]");
    }
}
