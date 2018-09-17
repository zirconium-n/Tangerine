#pragma once
#include <random>

#include <pcg/pcg_random.hpp>
#include <pcg/pcg_extras.hpp>

#include "IOChannel.h" 
namespace sgk {
	namespace utils {

		//default as D6
		class Dice: InputChannel<int> {
		public:
			Dice() :
				D_{ 6 },
				rng{ pcg_extras::seed_seq_from<std::random_device>{} }
			{}

			Dice(int D) :
				D_{ D },
				rng{ pcg_extras::seed_seq_from<std::random_device>{} }
			{}

			int D() {
				return D_;
			}

			int operator()() override{
				return rng(D_) + 1;
			}

		private:
			const int D_;
			pcg32 rng;
		};
	}
}