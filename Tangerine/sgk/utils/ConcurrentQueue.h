#pragma once
#include <mutex>
#include <queue>


namespace sgk {
	namespace utils{
		template<typename T>
		class ConcurrentQueue {
		public:
			class Pusher {
				friend class ConcurrentQueue<T>;
			public:
				void push(const T& value) const {
					cq_->push(value);
					return;
				}
				void push(T&& value) const {
					cq_->push(value);
					return;
				}

				void operator()(const T& value) const{
					this->push(value);
					return;
				}
				void operator()(T&& value) const {
					this->push(value);
					return;
				}

			private: 
				Pusher(ConcurrentQueue<T>* cq) :
					cq_(cq) {};
				ConcurrentQueue<T>* cq_;

				//not safe. change later;
			};


			using queue_type = std::queue<T>;

			ConcurrentQueue() = default;

			typename queue_type::size_type size(){
				std::lock_guard<std::mutex>	lock(mtx_);
				return q_.size();
			}

			T pop() {
				std::unique_lock<std::mutex> lock(mtx_);
				while (q_.empty()) {
					cond_.wait(lock);
				}
				auto value = q_.front();
				q_.pop();
				return value;
			}

			void push(const T& value) {
				std::lock_guard<std::mutex> lock(mtx_);
				q_.push(value);
				cond_.notify_one();
				return;
			}
			void push(T&& value) {
				std::lock_guard<std::mutex> lock(mtx_);
				q_.push(value);
				cond_.notify_one();
				return;
			}

			Pusher pusher() {
				return { this };
			}

		private:
			std::condition_variable cond_;
			std::mutex mtx_;
			queue_type q_;
		};
	}
}