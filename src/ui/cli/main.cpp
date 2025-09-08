#include "ab/rng.hpp"
#include "ab/campaign.hpp"
#include <locale>

int main() {
    setlocale(LC_ALL, "Russian");
    ab::IRng& rng = ab::defaultRng();
    ab::Campaign game(rng);
    bool ok = game.runInteractive();
    return ok ? 0 : 1;
}
