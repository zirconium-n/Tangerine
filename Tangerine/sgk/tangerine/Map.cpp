#include "Map.h"

namespace sgk {
	namespace tangerine {
		std::uint32_t Tile::linking_packed() const {
			return *reinterpret_cast<const std::uint32_t*>(&linking);
		}
		Map::Map(const int width, const int height) :
			width_(width),
			height_(height),
			tiles_(width * height)
		{
			//should check w, h > 0
		}
		Map::Map(const int width, const int height, std::istream & source) :
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
		const Tile & Map::tile(int x, int y) const {
			if (x < 0 || x >= width_ ||
				y < 0 || y >= height_) {
				throw std::out_of_range{ "Tile out of map" };
			}
			return tiles_[y * width_ + x];
		}
		Tile & Map::tile(int x, int y) {
			if (x < 0 || x >= width_ ||
				y < 0 || y >= height_) {
				throw std::out_of_range{ "Tile out of map" };
			}
			return tiles_[y * width_ + x];
		}
		int Map::width() const {
			return width_;
		}
		int Map::height() const {
			return height_;
		}
	}
}

void to_json(nlohmann::json & j, const sgk::tangerine::Tile & t) {
	j["type"] = t.type;
	j["linking"] = t.linking_packed();
	return;
}

void to_json(nlohmann::json & j, const sgk::tangerine::Map & m) {
	using namespace sgk::tangerine;
	j["height"] = m.height();
	j["width"] = m.width();
	for (int y = 0; y < m.height(); y++) {
		for (int x = 0; x < m.width(); x++) {
			j["tile"][y][x] = { m.tile(x, y) };
		}
	}
}
