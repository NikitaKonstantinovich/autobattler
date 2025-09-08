#include "ab/ui.hpp"
#include <iostream>

namespace ab::ui {

    void printSheet(const Character& c) {
        std::cout << "HP " << c.curHp() << "/" << c.maxHp()
            << "  STR " << c.stats().str
            << "  DEX " << c.stats().dex
            << "  END " << c.stats().endu
            << "  Weapon=" << c.weapon().name << " (" << c.weapon().baseDamage << ")\n";
        std::cout << "Levels: Rogue=" << c.levels().rogue
            << " Warrior=" << c.levels().warrior
            << " Barbarian=" << c.levels().barbarian
            << "  total=" << c.levels().total() << "\n";
    }

    void printMonster(const Monster& m) {
        std::cout << "Monster: " << m.name
            << "  HP " << m.maxHP
            << "  STR " << m.stats.str
            << "  DEX " << m.stats.dex
            << "  END " << m.stats.endu
            << "  Weapon=" << m.weapon.name << " (" << m.weapon.baseDamage << ")\n";
    }

    void printHeader(const std::string& title) {
        std::cout << "=== " << title << " ===\n";
    }

}
