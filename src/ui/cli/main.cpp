#include "ab/rng.hpp"
#include "ab/weapon.hpp"
#include "ab/character.hpp"
#include "ab/classes.hpp"
#include "ab/monster.hpp"
#include "ab/combat.hpp"
#include <iostream>

static void printSheet(const ab::Character& c) {
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

static void printMonster(const ab::Monster& m) {
    std::cout << "Monster: " << m.name
        << "  HP " << m.maxHP
        << "  STR " << m.stats.str
        << "  DEX " << m.stats.dex
        << "  END " << m.stats.endu
        << "  Weapon=" << m.weapon.name << " (" << m.weapon.baseDamage << ")\n";
}

int main() {
	setlocale(LC_ALL, "Russian");
    ab::IRng& rng = ab::defaultRng();

	ab::Character hero = ab::Character::createNew(rng, ab::ClassKind::Warrior);
    std::cout << "Created hero as " << ab::className(ab::ClassKind::Warrior) << "\n";
	printSheet(hero);

	ab::Monster m = ab::randomMonster(rng);
	printMonster(m);

    ab::Combatant A = ab::makePlayer(hero);
    ab::Combatant B = ab::makeMonster(m);
    ab::CombatEngine engine(rng);
    bool win = engine.duel(A, B);
    std::cout << (win ? "Result: WIN\n" : "Result: LOSS\n");


    return 0;
}
