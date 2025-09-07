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
		inline const Weapon Sword{ "���", WeaponType::Slashing, 3 };
		inline const Weapon Club{ "������", WeaponType::Bludgeoning, 3 };
		inline const Weapon Dagger{ "������", WeaponType::Piercing, 2 };
		inline const Weapon Axe{ "�����", WeaponType::Slashing, 4 };
		inline const Weapon Spear{ "�����", WeaponType::Piercing, 3 };
		inline const Weapon LegendarySword{ "����������� ���", WeaponType::Slashing, 10 };
	}

}