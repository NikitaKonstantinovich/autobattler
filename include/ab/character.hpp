#pragma once
#include "stats.hpp"
#include "weapon.hpp"
#include "classes.hpp"
#include "rng.hpp"

namespace ab {

    struct Character {
        Stats base{};
        ClassLevels levels{};
        Weapon weapon{ Weapons::Sword };
        int maxHP{ 1 };
        int curHP{ 1 };

        static Character createNew(IRng& rng, ClassKind start);
        void gainLevel(ClassKind chosen);
    };

} 
