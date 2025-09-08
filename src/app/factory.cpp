#include "ab/factory.hpp"
#include "ab/level.hpp"

namespace ab {

    Character HeroFactory::newHero(IRng& rng) {
        ClassKind start = LevelSystem::chooseNextClass(rng);
        Character h = Character::createNew(rng, start);
        LevelSystem::healFull(h);
        return h;
    }

}
