#include "ab/rng.hpp"
#include "ab/weapon.hpp"
#include <iostream>

int main() {
	setlocale(LC_ALL, "Russian");
    ab::IRng& rng = ab::default_rng();
    const ab::Weapon& w = ab::Weapons::Sword;

    std::cout << "Autobattler skeleton OK. rnd=" << rng.uniform(1, 6) << "\n";
    std::cout << "Weapon: " << w.name << " dmg=" << w.baseDamage
        << " type=" << ab::to_string(w.type) << "\n";
    return 0;
}
