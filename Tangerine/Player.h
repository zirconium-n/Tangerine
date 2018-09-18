#pragma once
#include <memory>
#include <map>
#include <vector>

#include "utils/IOChannel.h"

namespace sgk {
	namespace tangerine {
		enum class Norma {

		};

		class Card {

		};

		class CharactorDefinition {
		public:
			int hp_max;
			int atk, def, evd, rec;
			Card hyper;
		};


		class StatusEffect {


		};

		class Player {
		public:
			using input_ptr = std::shared_ptr<utils::intInput>;

			explicit Player(const CharactorDefinition& char_def, input_ptr input);

			int operator[](const std::string& key) const;
			int& operator[](const std::string& key);

		private:
			input_ptr input_;
			std::vector<StatusEffect> status_effects;
			const CharactorDefinition char_def_;
			std::map<std::string, int> attr_base;
			std::vector<Card> hand;
			Norma norma;
		};
	}
}