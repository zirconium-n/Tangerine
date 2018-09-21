#include "Player.h"
#include <iostream>

namespace sgk {
	namespace general {
		Player::Player(std::weak_ptr<Game> game, std::uint32_t id)
			:game_(game), id_(id) {};

		void Player::connect() {
			throw "notImplemented";
		}

		void Player::requestInt(int upper_bound, std::string instruction = "") {
			int x = 0;
			while (x <= 0 && x > upper_bound) {
				std::cout << instruction;
				std::cin >> x;
			}

		}

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

		void Player::apply(const StatusEffect<Player>& effect){
			status_effects.push_back(effect);
			return;
		}
	}
}