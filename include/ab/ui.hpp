#pragma once
#include "character.hpp"
#include "monster.hpp"
#include "classes.hpp" 
#include "combat.hpp"  
#include <string>

namespace ab::ui {
	void printSheet(const Character& c);
	void printMonster(const Monster& m);
	void printHeader(const std::string& title);

	ClassKind askClass(const std::string& title);
	bool askYesNo(const std::string& question);
	int askTargetWins(int defaultWins);

	class ConsoleCombatSink : public ICombatSink {
	public:
		void onRound(const CombatEvent& e) override;
	};
}
