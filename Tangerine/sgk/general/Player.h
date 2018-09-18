#pragma once
#include <memory>
#include <map>
#include <vector>
#include <list>

#include "sgk/utils/IOChannel.h"
#include "StatusEffect.h"

namespace sgk {
	namespace general {
		class Player {
		public:
			using InputPtr = std::shared_ptr<utils::intInput>;

			explicit Player(InputPtr input);

			int base(const std::string& attr) const;
			int& base(const std::string& attr);
			int actual(const std::string& attr) const;

			void react(const std::string& event_name);

			void apply(const StatusEffect<Player>& effect);

		private:
			InputPtr input_;

			std::list<StatusEffect<Player>> status_effects;
			std::map<std::string, int> attr_base;
		};
	}
}