#include "Player.h"

namespace sgk {
	namespace general {
		Player::Player(input_ptr input) :
			input_(input)
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