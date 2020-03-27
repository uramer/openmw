#pragma once
#ifndef OPENMW_MPSPLITTER_HPP
#define OPENMW_MPSPLITTER_HPP

#include <sstream>
#include <vector>

namespace Gui
{
    class MPSplitter
    {
        public:
            static const char DELIMETER;
            MPSplitter(): mStream() {
                mFirst = true;
            };
            static std::vector<std::string> split(std::string text);

            template<typename T>
            MPSplitter& operator<<(const T& obj);
            MPSplitter& operator<<(const std::string& obj);
            MPSplitter& operator<<(int obj);
            MPSplitter& operator<<(size_t obj);

            const std::string str() {
                return mStream.str();
            }
        protected:
            bool mFirst;
            std::ostringstream mStream;
    };
}
#endif //OPENMW_MPSPLITTER_HPP
