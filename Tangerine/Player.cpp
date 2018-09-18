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

		int Player::base(const std::string& key) const { 
			return attr_base.at(key); 
		}

		int& Player::base(const std::string& key) { 
			return attr_base.at(key); 
		}

		int Player::actual(const std::string& key) const{
			int value = base(key);
			for (auto& effect : status_effects) {
				effect.apply(*this, key, value);
			}
			return value;
		}

		void Player::react(const std::string& event_name) {
			auto iter = status_effects.begin();
			while (iter != status_effects.end()) {
				iter->react(*this, event_name);
				if (!iter->alive()) {
					iter = status_effects.erase(iter);
				}
				else {
					iter++;
				}
			}
			return;
		}
	}
}