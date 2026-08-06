#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <optional>

class ConfigReader {
public:
    ConfigReader() = default;

    bool load(const std::string& filename);

    std::string get_string(const std::string& key) const;
    double get_double(const std::string& key) const;
    int get_int(const std::string& key) const;
    bool get_bool(const std::string& key) const;

    std::optional<std::string> get_string_opt(const std::string& key) const;
    std::optional<double> get_double_opt(const std::string& key) const;
    std::optional<int> get_int_opt(const std::string& key) const;

    std::vector<double> get_double_array(const std::string& key) const;
    std::vector<int> get_int_array(const std::string& key) const;

    bool has_key(const std::string& key) const;
    void print_all() const;

private:
    std::unordered_map<std::string, std::string> values;

    std::string trim(const std::string& str) const;
    std::vector<std::string> split(const std::string& str, char delimiter) const;

    void validate_positive(const std::string& key, double value) const;
    void validate_range(const std::string& key, double value, double min, double max) const;
};
