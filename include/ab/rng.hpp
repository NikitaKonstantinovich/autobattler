#pragma once
namespace ab {

	struct IRng {
		virtual ~IRng() = default;
		virtual int uniform(int low, int high) = 0;
	};

	IRng& defaultRng();
}