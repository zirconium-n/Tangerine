#pragma once
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <cstddef>

#include <sgk/general/StatusEffect.h>
#include "Game.h"


namespace sgk {
	namespace general {
		class Player {
		public:
			Player(std::weak_ptr<Game> game, std::uint32_t id);
			//screw abstraction. do this later
			void connect();
			
			void requestInt(int upper_bound, std::string instruction = "");

			std::uint32_t id() const;
			std::weak_ptr<Game> game() const;

			int base(const std::string& attr) const;
			int& base(const std::string& attr);
			int actual(const std::string& attr) const;

			void react(const std::string& event_name);

			void apply(const StatusEffect<Player>& effect);

		private:
			std::list<StatusEffect<Player>> status_effects;
			std::map<std::string, int> attr_base;
			const std::weak_ptr<Game> game_;
			const std::uint32_t id_;
		};
	}
}