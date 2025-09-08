#include "ab/factory.hpp"
#include "ab/level.hpp"

namespace ab {

    Character HeroFactory::newHero(IRng& rng, ClassKind chosen) {
        Character h = Character::createNew(rng, chosen);
        LevelSystem::healFull(h);
        return h;
    }

}
