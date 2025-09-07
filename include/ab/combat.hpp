#pragma once
#include "stats.hpp"
#include "weapon.hpp"
#include "classes.hpp"
#include "character.hpp"
#include "monster.hpp"
#include "rng.hpp"
#include <string>

namespace ab {

    struct FighterState {
        int turnsAttacked{ 0 };
        bool firstAttackDone{ false };
    };

    struct Combatant {
        std::string name;
        int curHP{ 1 };
        int maxHP{ 1 };
        Stats stats{};
        Weapon weapon{ Weapons::Sword };
        const ClassLevels* classes{ nullptr };
        bool isPlayer{ false };
        FighterState state{};
    };

    Combatant makePlayer(const Character& c);
    Combatant makeMonster(const Monster& m);

    class CombatEngine {
    public:
        explicit CombatEngine(IRng& rng);
        int attack(Combatant& attacker, Combatant& defender);
        bool duel(Combatant a, Combatant b);
    private:
        IRng& rng_;
        bool missCheck(const Combatant& att, const Combatant& def);
    };

}
