#include "MPSplitter.hpp"

namespace Gui
{
    const char MPSplitter::DELIMETER = '|';

    std::vector<std::string> MPSplitter::split(std::string text) {
        size_t pos = 0;
        size_t searchpos = 0;
        size_t last = text.size() - 1;
        std::vector<std::string> result;
        do {
            size_t found = text.find(DELIMETER, searchpos);
            bool escaped = false;
            if (found < last && text.at(found + 1) == DELIMETER) {
                searchpos = found + 2;
                continue;
            }
            std::string segment;
            if (found == std::string::npos) {
                segment = text.substr(pos);
                pos = std::string::npos;
            }
            else {
                segment = text.substr(pos, found - 1);
                pos = found + 1;
                searchpos = found + 1;
            }
            result.push_back(segment);
        } while (pos != std::string::npos);
        return result;
    }

    template<typename T>
    MPSplitter& MPSplitter::operator<<(T& obj) {
        if (!mFirst) mStream << DELIMETER;
        std::ostringstream converter;
        converter << obj;
        return this->operator<<(converter.str());
    }

    MPSplitter& MPSplitter::operator<<(std::string obj) {
        if (!mFirst) mStream << DELIMETER;
        std::string text = obj;
        size_t pos = 0;
        do {
            size_t found = text.find(DELIMETER, pos);
            if (found == std::string::npos) {
                break;
            }
            mStream << text.substr(pos, found - pos + 1) << DELIMETER;
            pos = found + 1;
        } while (pos < text.size());
        mStream << text.substr(pos);
        mFirst = false;
        return *this;
    }

    MPSplitter& MPSplitter::operator<<(int obj) {
        if (!mFirst) mStream << DELIMETER;
        mStream << obj;
        mFirst = false;
        return *this;
    }

    MPSplitter& MPSplitter::operator<<(size_t obj) {
        if (!mFirst) mStream << DELIMETER;
        mStream << obj;
        mFirst = false;
        return *this;
    }
}
