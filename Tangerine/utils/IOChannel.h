#pragma once

namespace sgk {
	namespace utils{
		//no buffering for now

		template<typename T>
		class InputChannel {
		public:
			InputChannel() = default;

			InputChannel(InputChannel&) = delete;
			InputChannel& operator=(const InputChannel&) = delete;

			virtual T operator()() = 0;
		};

		using intInput = InputChannel<int>;

		template<typename T>
		class OutputChannel {
		public:
			OutputChannel() = default;

			OutputChannel(OutputChannel&) = delete;
			OutputChannel& operator=(const OutputChannel&) = delete;

			virtual void operator()(const T&) = 0;
		};
	}
}