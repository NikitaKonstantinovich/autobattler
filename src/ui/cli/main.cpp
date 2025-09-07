#include "ab/rng.hpp"
#include "ab/weapon.hpp"
#include "ab/character.hpp"
#include "ab/classes.hpp"
#include "ab/monster.hpp"
#include "ab/combat.hpp"
#include "ab/loot.hpp"
#include <iostream>
#include <iomanip>

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
    using namespace ab;

    IRng& rng = defaultRng();

    Character hero = Character::createNew(rng, ClassKind::Warrior);
    hero.gainLevel(ClassKind::Rogue);
    hero.gainLevel(ClassKind::Barbarian);

    std::cout << "=== Hero sheet ===\n";
    printSheet(hero);

    Monster mon = randomMonster(rng);
    std::cout << "=== Monster spawned ===\n";
    printMonster(mon);

    Combatant A = makePlayer(hero);
    Combatant B = makeMonster(mon);

    CombatEngine engine(rng);

    bool playerTurn = (A.stats.dex >= B.stats.dex);
    int roundNo = 1;

    std::cout << "=== Combat log ===\n";
    while (A.curHP > 0 && B.curHP > 0) {
        auto& att = playerTurn ? A : B;
        auto& def = playerTurn ? B : A;

        std::cout << "Round " << std::setw(2) << roundNo << " | "
            << (playerTurn ? "HERO" : "MON ")
            << " attacks ... ";

        int hpBefore = def.curHP;
        int dmg = engine.attack(att, def);

        if (dmg == 0) {
            std::cout << "MISS\n";
        }
        else {
            std::cout << "HIT " << dmg << "  | "
                << def.name << " HP: " << hpBefore << " -> " << def.curHP << "\n";
        }

        if (def.curHP <= 0) break;

        playerTurn = !playerTurn;
        ++roundNo;
    }

    bool win = (A.curHP > 0);
    std::cout << "=== Result: " << (win ? "WIN" : "LOSS") << " ===\n";

    if (win) {
        if (auto reward = LootSystem::rewardFromMonster(mon)) {
            std::cout << "Loot: " << reward->name << " (+" << reward->baseDamage << ")\n";
            bool equipped = LootSystem::autoEquip(hero, *reward);
            std::cout << (equipped ? "Equipped: " : "Kept current: ")
                << hero.weapon().name << " (+" << hero.weapon().baseDamage << ")\n";
        }
    }
    return 0;
}
