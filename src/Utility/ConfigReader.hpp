// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

class ConfigReader {
public:
    static nlohmann::json read(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filename);
        }

        nlohmann::json config;
        try {
            file >> config;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Ошибка парсинга JSON в файле " + filename +
                                   ": " + std::string(e.what()));
        }

        file.close();
        return config;
    }
};
