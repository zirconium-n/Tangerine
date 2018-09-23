#pragma once
#include <cstddef>
#include <any>
#include <nlohmann/json.hpp>

#include <sgk/network/websocket.h>
#include <sgk/utils/ConcurrentQueue.h>
#include <sgk/general/Player.h>
#include <sgk/general/typedef.h>

namespace sgk {
	namespace general {
		class Game {
		public:
			Game();

			using ResponseQueue =
				sgk::utils::ConcurrentQueue<Response>;

			void run();
		private:
			IO_Context ioc_;
			const ip::address address_;
			const unsigned short port_;
			tcp::acceptor acceptor_;

			const int player_count_;
			std::vector<std::unique_ptr<Player>> players_;
			ResponseQueue resp_queue_;

			std::vector<Json> responses;

			void broadcast(const nlohmann::json& data);
			void wait_responses();
		};
	}
}