#ifndef INIREADER_HPP
#define INIREADER_HPP

#include <unordered_map>
#include <istream>
#include <string>

// Writing my own INI reader because I like the challenge :3
// But fr, this'll be used for settings and stuff

namespace ini {
    enum IniTokenType {
        SECTION_START = 0x5B,   // [
        SECTION_END = 0x5D,     // ]
        DELIMITER = 0x3D,       // =
        COMMENT = 0x3E          // ;
    };

    class IniSection {
        public:
            IniSection(std::string name);
            ~IniSection();

            void add(std::string key, std::string value);
            
        private:
            std::string m_name;
            std::unordered_map<std::string, std::string> m_data;
            std::unordered_map<std::string, IniSection> m_subSections;

    };

    class IniReader {
        public:
            IniReader();
            IniReader(std::istream& stream);
            ~IniReader();

            void load(std::string path);
            void load(std::istream& stream);

            std::string get(std::string section, std::string key);
        
        private:
            std::unordered_map<std::string, IniSection> m_sections;
            std::istream* m_stream;
    };
}

#endif // INIREADER_HPP
