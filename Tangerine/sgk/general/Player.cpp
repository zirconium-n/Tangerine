#include "Player.h"

#include <iostream>
#include <sgk/utils/ConcurrentQueue.h>
#include <gsl/gsl>

namespace sgk {
	namespace general {
		
		Player::Player(ResponsePusher pusher, tcp::socket&& sock, std::uint32_t id)
			:pusher_(pusher), ws_(std::move(sock)), id_(id) {
			if (worker_.joinable()) {
				return;
			}
			ws_.accept();
			ws_.text();
			working_ = true;
			worker_ = std::thread{
				[this]() {this->work(); }
			};
		}
	
		void Player::work() {
			while (true) {
				auto request = request_queue_.pop();
				std::cout << request.dump();
				ws_.write(boost::asio::buffer(request.dump()));
				auto consume = gsl::finally([&]() {recv_buf_.consume(-1); });

				auto msg_len = ws_.read(recv_buf_);
				auto d = recv_buf_.data().data();
				Response r;
				r.id = id_;
				auto resp = static_cast<const char*>(d);
				auto str = std::string{ resp, resp + msg_len };
				r.data = Json::parse(str);
				std::cout << r.data.dump(4);
				pusher_.push(r);
			}

			working_ = false;
		}

		void Player::request(const Request& msg) {
			request_queue_.push(msg);
		}

		
		id_type Player::id() const{
			return id_;
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

		void Player::response(const Json& data){
			pusher_.push(Response{ this->id_, data });
			return;
		}
	}
}