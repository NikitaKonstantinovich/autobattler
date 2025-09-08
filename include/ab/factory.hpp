#pragma once
#include "character.hpp"
#include "classes.hpp"
#include "rng.hpp"

namespace ab {

    class HeroFactory {
    public:
        static Character newHero(IRng& rng);
    };

}
