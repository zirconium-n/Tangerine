#include <vector>
#include <memory>
#include <map>
#include <string>

#include "Player.h"

namespace sgk {
	namespace general {
		class Game {

		public:
			Game():
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
		};

	}
}