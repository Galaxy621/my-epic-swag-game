#include "settings.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

GameSettings::GameSettings(const char* source) : m_source(source) {
    // Load settings from file
    std::string settings;
    std::ifstream settingsStream(source);

    if (!settingsStream.is_open()) {
        std::cout << "Copying default settings" << std::endl;
        m_settings = defaultSettings;
    } else {
        std::string line;
        std::unordered_map<std::string, std::string> settingsMap;

        while (std::getline(settingsStream, line)) {
            std::istringstream lineStream(line);
            std::string key, value;

            std::getline(lineStream, key, '=');
            std::getline(lineStream, value);

            settingsMap[key] = value;
        }

        if (settingsMap["version"] != defaultSettings.at("version")) {
            for (auto& [key, value] : defaultSettings) {
                if (settingsMap.find(key) == settingsMap.end()) {
                    settingsMap[key] = value;
                }
            }
        }

        m_settings = settingsMap;
    }
}

GameSettings::~GameSettings() {
    if (m_settings["saveOnExit"] == "true")
        save();

    m_settings.clear();
}

void GameSettings::save() {    
    std::ofstream settingsStream(m_source);

    if (!settingsStream.is_open()) {
        throw std::runtime_error("Failed to open settings file for writing");
    }

    for (auto& [key, value] : m_settings) {
        settingsStream << key << "=" << value << std::endl;
    }
}

std::string GameSettings::get(std::string key) {
    return m_settings.at(key);
}

int GameSettings::get_int(std::string key) {
    return std::stoi(m_settings.at(key));
}

bool GameSettings::get_bool(std::string key) {
    return m_settings.at(key) == "true";
}

void GameSettings::set(const char* key, const char* value) {
    m_settings[key] = value;
}

void GameSettings::reset() {
    // clone defaultSettings to m_settings
    m_settings = defaultSettings;
}
