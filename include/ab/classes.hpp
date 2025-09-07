#pragma once
#include <string>

namespace ab {

    enum class ClassKind { Rogue = 1, Warrior = 2, Barbarian = 3 };

    inline int hpPerLevel(ClassKind c) {
        switch (c) {
        case ClassKind::Rogue: return 4;
        case ClassKind::Warrior: return 5;
        case ClassKind::Barbarian: return 6;
        }
        return 0;
    }

    inline const char* className(ClassKind c) {
        switch (c) {
        case ClassKind::Rogue: return "Разбойник";
        case ClassKind::Warrior: return "Воин";
        case ClassKind::Barbarian: return "Варвар";
        }
        return "?";
    }

    struct ClassLevels {
        int rogue{ 0 };
        int warrior{ 0 };
        int barbarian{ 0 };

        int total() const { return rogue + warrior + barbarian; }

        int level(ClassKind c) const {
            switch (c) {
            case ClassKind::Rogue: return rogue;
            case ClassKind::Warrior: return warrior;
            case ClassKind::Barbarian: return barbarian;
            }
            return 0;
        }

        void add(ClassKind c) {
            switch (c) {
            case ClassKind::Rogue: ++rogue; break;
            case ClassKind::Warrior: ++warrior; break;
            case ClassKind::Barbarian: ++barbarian; break;
            }
        }
    };

}
