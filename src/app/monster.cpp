#include "ab/monster.hpp"
#include "ab/rng.hpp"

namespace ab {

    Monster randomMonster(IRng& rng) {
        int k = rng.uniform(1, 6);
        Monster m;
        switch (k) {
        case 1:
            m = { "Гоблин", 5, {1,1,1}, Weapons::Dagger,
                 false,false,false,false,false, 2 };
            break;
        case 2:
            m = { "Скелет", 10, {2,2,1}, Weapons::Club,
                 true,false,false,false,false, 1 };
            break;
        case 3:
            m = { "Слайм", 8, {3,1,2}, Weapons::Spear,
                 false,true,false,false,false, 4 };
            break;
        case 4:
            m = { "Призрак", 6, {1,3,1}, Weapons::Sword,
                 false,false,true,false,false, 0 };
            break;
        case 5:
            m = { "Голем", 10, {3,1,3}, Weapons::Axe,
                 false,false,false,true,false, 3 };
            break;
        default:
            m = { "Дракон", 20, {3,3,3}, Weapons::LegendarySword,
                 false,false,false,false,true, 5 };
            break;
        }
        return m;
    }

} 
