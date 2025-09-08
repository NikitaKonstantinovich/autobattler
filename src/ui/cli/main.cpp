#include "ab/rng.hpp"
#include "ab/weapon.hpp"
#include "ab/character.hpp"
#include "ab/classes.hpp"
#include "ab/monster.hpp"
#include "ab/combat.hpp"
#include "ab/loot.hpp"
#include "ab/level.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>

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

static ab::Character newHero(ab::IRng& rng) {
    ab::ClassKind start = ab::LevelSystem::chooseNextClass(rng);
    ab::Character h = ab::Character::createNew(rng, start);
    return h;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    using namespace ab;

    int targetWins = 5;
    if (argc > 1) {
        targetWins = std::max(1, std::atoi(argv[1]));
    }

    IRng& rng = defaultRng();

    Character hero = newHero(rng);
    LevelSystem::healFull(hero);

    int streak = 0;
    int fightNo = 1;

    std::cout << "=== Campaign start: need " << targetWins << " wins in a row ===\n";
    printSheet(hero);

    while (streak < targetWins) {
        std::cout << "\n=== Fight #" << fightNo << " (streak " << streak << "/" << targetWins << ") ===\n";

        LevelSystem::healFull(hero);

        Monster mon = randomMonster(rng);
        std::cout << "Monster: " << mon.name
            << " | HP " << mon.maxHP
            << " | STR " << mon.stats.str
            << " | DEX " << mon.stats.dex
            << " | END " << mon.stats.endu
            << " | Weapon " << mon.weapon.name << " (" << mon.weapon.baseDamage << ")\n";

        Combatant A = makePlayer(hero);
        Combatant B = makeMonster(mon);
        CombatEngine engine(rng);

        bool win = engine.duel(A, B);

        std::cout << "Result: " << (win ? "WIN" : "LOSS") << "\n";

        if (win) {
            ++streak;

            if (auto reward = LootSystem::rewardFromMonster(mon)) {
                bool equipped = LootSystem::autoEquip(hero, *reward);
                std::cout << "Loot: " << reward->name << " (+" << reward->baseDamage << ") -> "
                    << (equipped ? "equipped" : "kept current") << "\n";
            }

            if (hero.levels().total() < 3) {
                LevelSystem::levelUpUntilTotal(hero, hero.levels().total() + 1, rng);
                std::cout << "After level-up:\n";
                printSheet(hero);
            }

            if (streak >= targetWins) break;
        }
        else {
            streak = 0;
            std::cout << "You died. Recreating hero...\n";
            hero = newHero(rng);
            LevelSystem::healFull(hero);
            printSheet(hero);
        }

        ++fightNo;
    }

    std::cout << "\n=== Campaign result: " << (streak >= targetWins ? "VICTORY" : "DEFEAT")
        << " (streak " << streak << "/" << targetWins << ") ===\n";

    return 0;
}
