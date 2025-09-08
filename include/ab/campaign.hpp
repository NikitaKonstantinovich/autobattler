#pragma once
#include "rng.hpp"

namespace ab {

    class Campaign {
    public:
        explicit Campaign(IRng& rng);
        bool runInteractive();
    private:
        IRng& rng_;
    };

}
