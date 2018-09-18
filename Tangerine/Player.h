#pragma once
#include <memory>
#include <map>
#include <vector>
#include <list>

#include "utils/IOChannel.h"
#include "StatusEffect.h"

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

		class Player {
		public:
			using input_ptr = std::shared_ptr<utils::intInput>;

			explicit Player(const CharactorDefinition& char_def, input_ptr input);

			int base(const std::string& attr) const;
			int& base(const std::string& attr);
			int actual(const std::string& attr) const;

			void react(const std::string& event_name);

		private:
			input_ptr input_;

			//list?
			std::list<StatusEffect<Player>> status_effects;
			const CharactorDefinition char_def_;
			std::map<std::string, int> attr_base;
			std::vector<Card> hand;
			Norma norma;
		};
	}
}