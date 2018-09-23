#pragma once
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <cstddef>
#include <any>
#include <thread>

#include <sgk/general/typedef.h>
#include <sgk/general/StatusEffect.h>
#include <sgk/utils/ConcurrentQueue.h>

#include <sgk/network/websocket.h>
#include <nlohmann/json.hpp>

namespace sgk {
	namespace general {
		class Game;
		class Player {
		public:

			using ResponsePusher = ResponseQueue::Pusher;

			//Player() = delete;
			~Player() = default;
			Player(ResponsePusher resp_pusher, tcp::socket&& sock, std::uint32_t id);
			//screw abstraction. do this later

			void request(const Request& msg);

			id_type id() const;

			int base(const std::string& attr) const;
			int& base(const std::string& attr);
			int actual(const std::string& attr) const;
			void react(const std::string& event_name);
			void apply(const StatusEffect<Player>& effect);

		private:
			const id_type id_;

			std::list<StatusEffect<Player>> status_effects;
			std::map<std::string, int> attr_base;

			void response(const Json& data);
			const ResponsePusher pusher_;

			RequestQueue request_queue_;
			void work();
			boost::beast::flat_buffer recv_buf_;
			Websocket ws_;

			bool working_ = false;
			std::thread worker_;
		};
	}
}