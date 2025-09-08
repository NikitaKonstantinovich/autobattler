#pragma once
#include "rng.hpp"

namespace ab {

    class Campaign {
    public:
        explicit Campaign(IRng& rng);
        bool run(int targetWins);
    private:
        IRng& rng_;
    };

}
