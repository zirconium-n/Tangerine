#include "Player.h"

namespace sgk {
	namespace tangerine {
		Player::Player(const CharactorDefinition& char_def, input_ptr input) :
			input_(input),
			char_def_(char_def),
			attr_base{
				{"hp", char_def.hp_max},
				{"hp_max", char_def.hp_max},
				{"stars", 0},
				{"wins", 0},
		}
		{}

		int Player::operator[](const std::string& key) const { 
			return attr_base.at(key); 
		}

		int& Player::operator[](const std::string& key) { 
			return attr_base.at(key); 
		}

	}
}