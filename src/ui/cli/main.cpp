#include "ab/rng.hpp"
#include "ab/weapon.hpp"
#include "ab/character.hpp"
#include "ab/classes.hpp"
#include <iostream>

static void printSheet(const ab::Character& c) {
    std::cout << "HP " << c.curHP << "/" << c.maxHP
        << "  STR " << c.base.str
        << "  DEX " << c.base.dex
        << "  END " << c.base.endu
        << "  Weapon=" << c.weapon.name << " (" << c.weapon.baseDamage << ")\n";
    std::cout << "Levels: Rogue=" << c.levels.rogue
        << " Warrior=" << c.levels.warrior
        << " Barbarian=" << c.levels.barbarian
        << "  total=" << c.levels.total() << "\n";
}

int main() {
	setlocale(LC_ALL, "Russian");
    ab::IRng& rng = ab::defaultRng();

	ab::Character hero = ab::Character::createNew(rng, ab::ClassKind::Warrior);
    std::cout << "Created hero as " << ab::className(ab::ClassKind::Warrior) << "\n";
	printSheet(hero);

	hero.gainLevel(ab::ClassKind::Rogue);
    std::cout << "After level-up to " << ab::className(ab::ClassKind::Rogue) << "\n";
    printSheet(hero);

    return 0;
}
