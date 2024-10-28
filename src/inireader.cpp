#include "inireader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>


ini::IniReader::IniReader() {
    m_stream = nullptr;
}

ini::IniReader::IniReader(std::istream& stream) {
    m_stream = &stream;
}

ini::IniReader::~IniReader() {
    if (m_stream) {
        delete m_stream;
    }
}

void ini::IniReader::load(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Failed to open file");

    load(file);
    file.close();
}

void ini::IniReader::load(std::istream& stream) {
    m_stream = &stream;

    std::string line;
    std::string section;

    // TODO
}