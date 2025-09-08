#pragma once
#include "character.hpp"
#include "monster.hpp"
#include <string>

namespace ab::ui {
	void printSheet(const Character& c);
	void printMonster(const Monster& m);
	void printHeader(const std::string& title);
}
