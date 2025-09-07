#pragma once
#include "stats.hpp"
#include "weapon.hpp"
#include "classes.hpp"
#include "rng.hpp"

namespace ab {

    class Character {
    public:
        static Character createNew(IRng& rng, ClassKind start);

        const Stats& stats() const;
        const ClassLevels& levels() const;
        const Weapon& weapon() const;
        int maxHp() const;
        int curHp() const;

        void gainLevel(ClassKind chosen);
        void equip(const Weapon& w);
        void healFull();
        void takeDamage(int dmg);

    private:
        Stats base_{};
        ClassLevels levels_{};
        Weapon weapon_{ Weapons::Sword };
        int maxHP_{ 1 };
        int curHP_{ 1 };
    };

}
