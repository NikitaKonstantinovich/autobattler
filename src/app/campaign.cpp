#include "ab/campaign.hpp"
#include "ab/factory.hpp"
#include "ab/level.hpp"
#include "ab/loot.hpp"
#include "ab/combat.hpp"
#include "ab/monster.hpp"
#include "ab/ui.hpp"
#include <iostream>
#include <algorithm>

namespace ab {

    Campaign::Campaign(IRng& rng) : rng_(rng) {}

    bool Campaign::run(int targetWins) {
        int streak = 0;
        int fightNo = 1;

        Character hero = HeroFactory::newHero(rng_);
        ui::printHeader("Campaign start");
        ui::printSheet(hero);

        while (streak < targetWins) {
            ui::printHeader(std::string("Fight #") + std::to_string(fightNo) + " (streak " + std::to_string(streak) + "/" + std::to_string(targetWins) + ")");

            LevelSystem::healFull(hero);

            Monster mon = randomMonster(rng_);
            ui::printMonster(mon);

            Combatant A = makePlayer(hero);
            Combatant B = makeMonster(mon);
            CombatEngine engine(rng_);
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
                    LevelSystem::levelUpUntilTotal(hero, hero.levels().total() + 1, rng_);
                    ui::printHeader("After level-up");
                    ui::printSheet(hero);
                }

                if (streak >= targetWins) break;
            }
            else {
                streak = 0;
                std::cout << "You died. Recreating hero...\n\n";
                hero = HeroFactory::newHero(rng_);
                ui::printSheet(hero);
            }

            ++fightNo;
        }

        ui::printHeader(std::string("Campaign result: ") + (streak >= targetWins ? "VICTORY" : "DEFEAT"));
        return streak >= targetWins;
    }

}
