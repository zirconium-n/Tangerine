#include <vector>
#include <exception>
#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace sgk {
namespace oj {


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
		static char type_to_char(Type t){
			return " oCedbpwDBP.......K.EmMvVsihH"[(std::uint32_t)t];
		}

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

	};

	static_assert(sizeof(Tile) == 8, "size of Tile is not 8");

	class Map {
	public:
		//maybe provide resize
		Map() = delete; 

		Map(const int width,const int height) :
			width_(width),
			height_(height),
			tiles_(width * height)
		{
			//should check w, h > 0
		}


		Map(const int width,const int height, std::istream& source) :
			width_(width),
			height_(height),
			tiles_(width * height) 
		{
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					source.read(reinterpret_cast<char*>(&tile(x, y)), sizeof(Tile));
				}
			}
		}

		[[nodiscard]]
		const Tile& tile(int x, int y) const {
			if (x < 0 || x >= width_ ||
				y < 0 || y >= height_) {
				throw std::out_of_range{ "Tile out of map" };
			}
			return tiles_[y * width_ + x];
		}

		[[nodiscard]]
		Tile& tile(int x, int y)  {
			if (x < 0 || x >= width_ ||
				y < 0 || y >= height_) {
				throw std::out_of_range{ "Tile out of map" };
			}
			return tiles_[y * width_ + x];
		}

		std::string toString() const{
			std::stringstream ss;
			ss << "\n";
			for (int y = 0; y < height_; y++) {
				for (int x = 0; x < width_; x++) {
					ss << Tile::type_to_char(tile(x, y).type);
				}
				ss << "\n";
			}
			return ss.str();
		}

	private:
		int width_;
		int height_;
		std::vector<Tile> tiles_;
	};
}
}


int main() {
	std::ifstream f{ "field_clover.fld" };
	using sgk::oj::Map;
	Map m{ 11, 11, f };
	std::cout << m.toString();


	system("pause");
	return 0;
}
