#include "ab/campaign.hpp"
#include "ab/factory.hpp"
#include "ab/level.hpp"
#include "ab/loot.hpp"
#include "ab/combat.hpp"
#include "ab/monster.hpp"
#include "ab/ui.hpp"
#include <iostream>

namespace ab {

    Campaign::Campaign(IRng& rng) : rng_(rng) {}

    bool Campaign::runInteractive() {
        int targetWins = ui::askTargetWins(5);

        int streak = 0;
        int fightNo = 1;

        ClassKind start = ui::askClass("����� ���������� ������");
        Character hero = HeroFactory::newHero(rng_, start);

        std::cout << "=== �������� ��������. ����� ����� ������: " << targetWins << " ===\n";

        while (streak < targetWins) {
            std::cout << "\n=== ��� #" << fightNo << " (����� " << streak << "/" << targetWins << ") ===\n";

            LevelSystem::healFull(hero);

            Monster mon = randomMonster(rng_);
            ui::printMonster(mon);

            Combatant A = makePlayer(hero);
            Combatant B = makeMonster(mon);
            CombatEngine engine(rng_);
            ui::ConsoleCombatSink sink;
            bool win = engine.duel(A, B, &sink);

            std::cout << "���������: " << (win ? "������" : "���������") << "\n";

            if (win) {
                ++streak;

                LevelSystem::healFull(hero);

                if (auto reward = LootSystem::rewardFromMonster(mon)) {
                    LootSystem::promptEquip(hero, *reward);
                }

                if (hero.levels().total() < 3) {
                    LevelSystem::promptOneLevelUp(hero);
                }

                if (streak >= targetWins) break;
            }
            else {
                streak = 0;
                std::cout << "�� �������. ������ ������ �����...\n";
                ClassKind s2 = ui::askClass("����� ���������� ������");
                hero = HeroFactory::newHero(rng_, s2);
            }

            ++fightNo;
        }

        std::cout << "\n=== ���� ��������: " << (streak >= targetWins ? "������" : "������")
            << " (����� " << streak << "/" << targetWins << ") ===\n";
        return streak >= targetWins;
    }

}
