#pragma once
#include "character.hpp"
#include "classes.hpp"
#include "rng.hpp"

namespace ab {

    class LevelSystem {
    public:
        static void healFull(Character& hero);
        static void grantLevel(Character& hero, ClassKind cls);
        static ClassKind chooseNextClass(IRng& rng);
        static void levelUpUntilTotal(Character& hero, int targetTotal, IRng& rng);
        static void promptOneLevelUp(Character& hero);
    };

}
