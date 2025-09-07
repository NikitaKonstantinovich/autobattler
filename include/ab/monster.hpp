#pragma once
#include "stats.hpp"
#include "weapon.hpp"
#include <string>

namespace ab {

    struct Monster {
        std::string name;
        int maxHP{ 1 };
        Stats stats{};
        Weapon weapon{ Weapons::Sword };

        bool takesDoubleFromBludgeoning{ false };
        bool immuneToSlashingWeaponBase{ false };
        bool hasHiddenAttackLikeRogue{ false };
        bool hasStoneSkinLikeBarbarian{ false };
        bool hasDragonBreath{ false };

        int rewardIndex{ 0 };
    };

    Monster randomMonster(class IRng& rng);

}
