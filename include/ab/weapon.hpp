#pragma once
#include "types.hpp"
#include <string>

namespace ab {
	struct Weapon {
		std::string name;
		WeaponType type{ WeaponType::Slashing };
		int baseDamage{ 0 };
	};

	namespace Weapons {
		inline const Weapon Sword{ "Меч", WeaponType::Slashing, 3 };
		inline const Weapon Club{ "Дубина", WeaponType::Bludgeoning, 3 };
		inline const Weapon Dagger{ "Кинжал", WeaponType::Piercing, 2 };
		inline const Weapon Axe{ "Топор", WeaponType::Slashing, 4 };
		inline const Weapon Spear{ "Копьё", WeaponType::Piercing, 3 };
		inline const Weapon LegendarySword{ "Легендарный меч", WeaponType::Slashing, 10 };
	}

}