#pragma once
#include <string_view>

namespace ab {

	enum class WeaponType {
		Slashing,
		Bludgeoning,
		Piercing
	};

	inline std::string_view to_string(WeaponType t) {
		switch (t) {
			case ab::WeaponType::Slashing: return "Рубящий";
			case ab::WeaponType::Bludgeoning: return "Дробящий";
			case ab::WeaponType::Piercing: return "Колющий";
		}
		return "?";
	}

}