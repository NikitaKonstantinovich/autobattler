#include "ab/rng.hpp"
#include <random>
#include <chrono>

namespace ab {

	class RngMersenne : public IRng {
	public:
		RngMersenne() {
			auto seed = static_cast<unsigned>(
				std::chrono::high_resolution_clock::now().time_since_epoch().count()
				);
			gen_.seed(seed);
		}
		int uniform(int low, int high) override {
			std::uniform_int_distribution<int> dist(low, high);
			return dist(gen_);
		}

	private:
		std::mt19937 gen_;
	};

	IRng& defaultRng() {
		static RngMersenne g;
		return g;
	}

}