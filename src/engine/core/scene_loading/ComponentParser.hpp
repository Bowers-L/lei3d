#pragma once

#include "core/Entity.hpp"

#include <fstream>
#include <string>
#include <unordered_map>

namespace lei3d
{
	extern std::unordered_map<std::string, void (*) (std::ifstream&, Entity&)> componentParsers;
}