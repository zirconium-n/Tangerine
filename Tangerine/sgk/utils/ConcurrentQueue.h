#pragma once
#include <mutex>
#include <queue>


namespace sgk {
	namespace utils{
		template<typename T>
		class ConcurrentQueue {
		public:
			using queue_type = std::queue<T>;

			ConcurrentQueue() = default;
			T& front() {
				std::unique_lock<std::mutex> lock(mtx_);
				while(q_.empty()) {
					cond_.wait(lock);
				}
				return q_.front();
			}

			queue_type::size_type size(){
				std::lock_guard<std::mutex>	lock(mtx_);
				return q_.size();
			}

			void pop() {
				std::unique_lock<std::mutex> lock(mtx_);
				while (q_.empty()) {
					cond_.wait(lock);
				}
				q_.pop();
				return;
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

		private:
			std::condition_variable cond_;
			std::mutex mtx_;
			queue_type q_;
		};
	}
}