#include "ab/rng.hpp"
#include <iostream>

int main() {
    ab::IRng& rng = ab::default_rng();
    std::cout << "Autobattler skeleton OK. rnd=" << rng.uniform(1, 6) << "\n";
    return 0;
}
