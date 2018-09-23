#pragma once
#include <cstddef>
#include <nlohmann/json.hpp>
#include <sgk/utils/ConcurrentQueue.h>

namespace sgk {
	namespace general {
		using Json = nlohmann::json;
		using id_type = std::uint32_t;
		using Request = Json;

		struct Response {
			id_type id;
			nlohmann::json data;
		};

		using RequestQueue = sgk::utils::ConcurrentQueue<Request>;
		using ResponseQueue = sgk::utils::ConcurrentQueue<Response>;
	}
}