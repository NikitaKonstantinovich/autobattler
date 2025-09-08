#include "ab/loot.hpp"
#include "ab/ui.hpp"
#include <iostream>

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

    bool LootSystem::promptEquip(Character& hero, const Weapon& reward) {
        const Weapon& cur = hero.weapon();
        std::cout << "����: " << reward.name << " (+" << reward.baseDamage << ")\n";
        std::cout << "�������: " << cur.name << " (+" << cur.baseDamage << ")\n";
        bool want = ui::askYesNo("�������� ������� ������?");
        if (want) {
            hero.equip(reward);
            std::cout << "�����������: " << hero.weapon().name << " (+" << hero.weapon().baseDamage << ")\n";
            return true;
        }
        std::cout << "��������� ������� ������.\n";
        return false;
    }

}
