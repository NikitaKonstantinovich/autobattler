#include "ab/loot.hpp"

namespace ab {

    std::optional<Weapon> LootSystem::rewardFromMonster(const Monster& m) {
        switch (m.rewardIndex) {
        case 1: return Weapons::Club;
        case 2: return Weapons::Dagger;
        case 3: return Weapons::Axe;
        case 4: return Weapons::Spear;
        case 5: return Weapons::LegendarySword;
        default: return std::nullopt;
        }
    }

    bool LootSystem::autoEquip(Character& hero, const Weapon& reward) {
        const Weapon& cur = hero.weapon();
        if (reward.baseDamage > cur.baseDamage) {
            hero.equip(reward);
            return true;
        }
        return false;
    }

}
