#include "MPSplitter.hpp"

namespace Gui
{
    const char MPSplitter::DELIMETER = '|';

    std::vector<std::string> MPSplitter::split(std::string text) {
        size_t pos = 0;
        size_t searchpos = 0;
        size_t last = text.size() - 1;
        std::string segment = "";
        std::vector<std::string> result;
        do {
            size_t found = text.find(DELIMETER, searchpos);
            if (found < last && text.at(found + 1) == DELIMETER) {
                segment += text.substr(pos, found - pos + 1);
                pos = found + 2;
                searchpos = found + 2;
                continue;
            }
            if (found == std::string::npos) {
                segment += text.substr(pos);
                pos = std::string::npos;
            }
            else {
                segment += text.substr(pos, found - pos);
                pos = found + 1;
                searchpos = found + 1;
            }
            result.push_back(segment);
            segment = "";
        } while (pos != std::string::npos);
        return result;
    }

    template<typename T>
    MPSplitter& MPSplitter::operator<<(const T& obj) {
        if (!mFirst) mStream << DELIMETER;
        std::ostringstream converter;
        converter << obj;
        return this->operator<<(converter.str());
    }

    MPSplitter& MPSplitter::operator<<(const std::string& obj) {
        if (!mFirst) mStream << DELIMETER;
        size_t pos = 0;
        size_t size = obj.size();
        do {
            size_t found = obj.find(DELIMETER, pos);
            if (found == std::string::npos) {
                break;
            }
            mStream << obj.substr(pos, found - pos + 1) << DELIMETER;
            pos = found + 1;
        } while (pos < size);
        mStream << obj.substr(pos);
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
