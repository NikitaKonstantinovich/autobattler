#include "ab/character.hpp"

namespace ab {

    static void applyClassImmediateBonus(Character& c, ClassKind ck, int newLevel) {
        if (ck == ClassKind::Rogue) {
            if (newLevel == 2) c.base.dex += 1;
        }
        else if (ck == ClassKind::Warrior) {
            if (newLevel == 3) c.base.str += 1;
        }
        else {
            if (newLevel == 3) c.base.endu += 1;
        }
    }

    Character Character::createNew(IRng& rng, ClassKind start) {
        Character ch;
        ch.base.str = rng.uniform(1, 3);
        ch.base.dex = rng.uniform(1, 3);
        ch.base.endu = rng.uniform(1, 3);

        if (start == ClassKind::Rogue) ch.weapon = Weapons::Dagger;
        else if (start == ClassKind::Warrior) ch.weapon = Weapons::Sword;
        else  ch.weapon = Weapons::Club;

        ch.maxHP = 0;
        ch.curHP = 0;
        ch.gainLevel(start);
        return ch;
    }

    void Character::gainLevel(ClassKind chosen) {
        int next = levels.level(chosen) + 1;
        applyClassImmediateBonus(*this, chosen, next);
        levels.add(chosen);
        maxHP += hpPerLevel(chosen) + base.endu;
        curHP = maxHP;
    }

}