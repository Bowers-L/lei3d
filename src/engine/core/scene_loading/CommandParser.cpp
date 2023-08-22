#include "CommandParser.hpp"

#include "util/StringUtil.hpp"

namespace lei3d
{
    void ParseModel(std::ifstream& fileStream)
    {
        std::string line;
        while (fileStream.good() && std::getline(fileStream, line))
        {
            if (strContains(line, "faces"))
            {
            }
        }
    }

    std::unordered_map<std::string, void (*) (std::ifstream&)> commandParsers = {
        {"Model", ParseModel}
    };
}
