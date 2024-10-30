#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <cstdint>
#include <unordered_map>
#include <string>
#include <memory>

// ngl probably just gonna make my own format
// no need for sections, just key value pairs

const std::unordered_map<std::string, std::string> defaultSettings = {
    {"version", "1.0"},
    {"width", "1280"},
    {"height", "720"},
    {"vsync", "true"},
    {"saveOnExit", "true"}
};

class GameSettings {
    public:
        GameSettings(const char* source);
        ~GameSettings();

        void save();
        
        std::string get(std::string key);
        int32_t get_int(std::string key);
        bool get_bool(std::string key);

        void set(const char* key, const char* value);
        void reset();

    private:
        const char* m_source;
        std::unordered_map<std::string, std::string> m_settings;
};

typedef std::shared_ptr<GameSettings> GameSettingsPtr;

#endif // SETTINGS_HPP