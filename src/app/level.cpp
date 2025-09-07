#include "ab/level.hpp"

namespace ab {

    void LevelSystem::healFull(Character& hero) {
        hero.healFull();
    }

    void LevelSystem::grantLevel(Character& hero, ClassKind cls) {
        hero.gainLevel(cls);
    }

    ClassKind LevelSystem::chooseNextClass(IRng& rng) {
        int k = rng.uniform(1, 3);
        if (k == 1) return ClassKind::Rogue;
        if (k == 2) return ClassKind::Warrior;
        return ClassKind::Barbarian;
    }

    void LevelSystem::levelUpUntilTotal(Character& hero, int targetTotal, IRng& rng) {
        while (hero.levels().total() < targetTotal) {
            ClassKind cls = chooseNextClass(rng);
            grantLevel(hero, cls);
        }
    }

}
