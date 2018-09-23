#include <sgk/general/Game.h>


int main() {
	nlohmann::json j;

	sgk::general::Game game;
	game.run();
	return 0;
}