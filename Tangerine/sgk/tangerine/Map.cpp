#include "Map.h"

namespace sgk {
	namespace tangerine {
		inline std::uint32_t Tile::linking_packed() const {
			return *reinterpret_cast<const std::uint32_t*>(&linking);
		}
		inline Map::Map(const int width, const int height) :
			width_(width),
			height_(height),
			tiles_(width * height)
		{
			//should check w, h > 0
		}
		inline Map::Map(const int width, const int height, std::istream & source) :
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
		inline const Tile & Map::tile(int x, int y) const {
			if (x < 0 || x >= width_ ||
				y < 0 || y >= height_) {
				throw std::out_of_range{ "Tile out of map" };
			}
			return tiles_[y * width_ + x];
		}
		inline Tile & Map::tile(int x, int y) {
			if (x < 0 || x >= width_ ||
				y < 0 || y >= height_) {
				throw std::out_of_range{ "Tile out of map" };
			}
			return tiles_[y * width_ + x];
		}
		inline int Map::width() const {
			return width_;
		}
		inline int Map::height() const {
			return height_;
		}
	}
}
