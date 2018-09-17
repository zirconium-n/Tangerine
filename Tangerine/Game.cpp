#include <vector>
#include <memory>

#include "utils/IOChannel.h"
#include "utils/Dice.h"

namespace sgk {
	namespace oj {
		class CharactorDefinition {

		};

		class Card {

		};

		class StatusEffect {


		};

		class Player {
		public:
			enum class Norma {

			};

			std::unique_ptr<utils::intInput> input;
			
			//dynamic properties

			std::vector<StatusEffect> status_effects;

		private:
			const CharactorDefinition char_def;
			int x, y, hp, hp_max, stars, wins;
			std::vector<Card> hand;
			Norma norma;
		};

		class OrangeGame {
			using Dice = sgk::utils::Dice;

		public:
			OrangeGame():
				player_count{4},
				players{player_count}
			{}

		private:

			const int player_count;
			std::vector<Player> players;
			Dice dice;
		};

	}
}