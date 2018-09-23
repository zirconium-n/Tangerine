#include <vector>
#include <memory>
#include <map>
#include <string>
#include <chrono>
#include <algorithm>

#include <sgk/general/Game.h>
#include <sgk/general/Player.h>

namespace sgk {
	namespace general {
		Game::Game() :
			ioc_{ 1 },
			address_{ ip::make_address("127.0.0.1") },
			port_{ 9090 },
			acceptor_{ ioc_, {address_, port_} },
			player_count_{ 2 },
			players_{ player_count_ },
			responses{ player_count_ }
		{
			int connected_ = 0;
			while (connected_ < player_count_) {
				try {
					auto ptr = std::make_unique<Player>(resp_queue_.pusher(), acceptor_.accept(), connected_);
					players_[connected_] = std::move(ptr);
					std::cout << "Player " << connected_ << " connected.";
					connected_++;
				}
				catch (const std::exception& e) {
					std::cerr << "Error:" << e.what() << std::endl;
				}
			}

			run();
		}

		void Game::run() {
			while (1) {
				/********************/
				//send request
				for (auto& player : players_) {
					Request req;
					req["type"] = "request";
					req["msg"] = "baka";
					player->request(req);
				}
				wait_responses();
				//process request
				Request req;
				int sum = 0;
				for (int i = 0; i < player_count_; i++) {
					int v = responses[i]["value"];
					sum += i;
					req[i]["value"] = v;
				}
				broadcast(req);
			}
			return;
		}

		void Game::broadcast(const nlohmann::json& data) {
			for (auto& player : players_) {
				player->request(data);
			}
			return;
		}

		void Game::wait_responses() {
			responses.clear();
			responses.resize(player_count_);
			int response_count = 0;
			while (response_count != player_count_) {
				auto resp = resp_queue_.pop();
				responses[resp.id] = resp.data;
				response_count++;
			}
			return;
		}
	}
}