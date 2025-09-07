#include "ab/character.hpp"

namespace ab {

    static void applyClassImmediateBonus(Character& c, ClassKind ck, int newLevel) {
        if (ck == ClassKind::Rogue) {
            if (newLevel == 2) const_cast<Stats&>(c.stats()).dex += 1;
        }
        else if (ck == ClassKind::Warrior) {
            if (newLevel == 3) const_cast<Stats&>(c.stats()).str += 1;
        }
        else {
            if (newLevel == 3) const_cast<Stats&>(c.stats()).endu += 1;
        }
    }

    Character Character::createNew(IRng& rng, ClassKind start) {
        Character ch;
        ch.base_.str = rng.uniform(1, 3);
        ch.base_.dex = rng.uniform(1, 3);
        ch.base_.endu = rng.uniform(1, 3);

        if (start == ClassKind::Rogue) ch.weapon_ = Weapons::Dagger;
        else if (start == ClassKind::Warrior) ch.weapon_ = Weapons::Sword;
        else  ch.weapon_ = Weapons::Club;

        ch.maxHP_ = 0;
        ch.curHP_ = 0;
        ch.gainLevel(start);
        return ch;
    }

    const Stats& Character::stats() const { return base_; }
    const ClassLevels& Character::levels() const { return levels_; }
    const Weapon& Character::weapon() const { return weapon_; }
    int Character::maxHp() const { return maxHP_; }
    int Character::curHp() const { return curHP_; }

    void Character::gainLevel(ClassKind chosen) {
        int next = levels_.level(chosen) + 1;
        applyClassImmediateBonus(*this, chosen, next);
        levels_.add(chosen);
        maxHP_ += hpPerLevel(chosen) + base_.endu;
        curHP_ = maxHP_;
    }

    void Character::equip(const Weapon& w) {
        weapon_ = w;
    }

    void Character::healFull() {
        curHP_ = maxHP_;
    }

    void Character::takeDamage(int dmg) {
        if (dmg <= 0) return;
        curHP_ -= dmg;
        if (curHP_ < 0) curHP_ = 0;
    }

}