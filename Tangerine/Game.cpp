#include <vector>
#include <memory>
#include <map>
#include <string>

#include "utils/IOChannel.h"
#include "utils/Dice.h"
#include "Player.h"

namespace sgk {
	namespace tangerine {
		class OrangeGame {
			using Dice = sgk::utils::Dice;

		public:
			OrangeGame():
				player_count{4},
				players{player_count}
			{}

			void start() {
				game_start();
			}
		private:

			void game_start() {

			}



			const int player_count;
			std::vector<Player> players;
			Dice dice;
		};

	}
}