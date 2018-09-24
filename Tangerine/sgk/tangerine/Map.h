#include <vector>
#include <exception>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace sgk {
namespace tangerine {

	struct Tile {
		enum class Type {
			Void = 0,
			Neutral = 1,
			Check = 2,
			Encounter = 3,
			Draw = 4,
			Bonus = 5,
			Drop = 6,
			Warp = 7,
			Draw_2 = 8,
			Bonus_2 = 9,
			Drop_2 = 10,
			Deck = 18,
			Encounter_2 = 20,
			Move = 21,
			Move_2 = 22,
			WarpMove = 23,
			WarpMove_2 = 24,
			Snow = 25,
			Ice = 26,
			Heal = 27,
			Heal_2 = 28,

		};

		Type type : 32;

		struct Linking {
			unsigned up : 1;
			unsigned right : 1;
			unsigned down : 1;
			unsigned left : 1;
			unsigned up_r : 1;
			unsigned right_r : 1;
			unsigned down_r : 1;
			unsigned left_r : 1;
			unsigned padding : 24;
		} linking;

		std::uint32_t linking_packed() const;
	};

	static_assert(sizeof(Tile) == 8, "size of Tile is not 8");
	static_assert(sizeof(Tile::Linking) == sizeof(std::uint32_t), "size of Linking is not 4");

	class Map {
	public:
		//maybe provide resize
		Map() = delete; 

		Map(const int width, const int height);

		Map(const int width, const int height, std::istream& source);

		const Tile& tile(int x, int y) const;
		Tile& tile(int x, int y);

		int width() const;
		int height() const;

	private:
		int width_;
		int height_;
		std::vector<Tile> tiles_;
	};
}
}

void to_json(nlohmann::json &j, const sgk::tangerine::Tile& t) {
	j["type"] = t.type;
	j["linking"] = t.linking_packed();
	return;
}

void to_json(nlohmann::json &j, const sgk::tangerine::Map& m) {
	using namespace sgk::tangerine;
	j["height"] = m.height();
	j["width"] = m.width();
	for (int y = 0; y < m.height(); y++) {
		for (int x = 0; x < m.width(); x++) {
			j["tile"][y][x] = { m.tile(x, y) };
		}
	}
}