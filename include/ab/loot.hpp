#pragma once
#include "weapon.hpp"
#include "monster.hpp"
#include "character.hpp"
#include <optional>

namespace ab {

    class LootSystem {
    public:
        static std::optional<Weapon> rewardFromMonster(const Monster& m);
        static bool autoEquip(Character& hero, const Weapon& reward);
        static bool promptEquip(Character& hero, const Weapon& reward);
    };

} 
