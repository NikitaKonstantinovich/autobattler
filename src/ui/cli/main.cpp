#include "ab/rng.hpp"
#include "ab/campaign.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");

    int targetWins = 5;
    if (argc > 1) {
        targetWins = std::max(1, std::atoi(argv[1]));
    }

    ab::IRng& rng = ab::defaultRng();
    ab::Campaign game(rng);
    bool ok = game.run(targetWins);
    std::cout << (ok ? "Game completed\n" : "Game failed\n");
    return ok ? 0 : 1;
}
