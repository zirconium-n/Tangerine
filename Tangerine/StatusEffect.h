#pragma once
#include <map>
#include <string>
#include <functional>

namespace sgk {
	namespace tangerine {
		template<typename Owner_T>
		class StatusEffect {
		public:
			StatusEffect();

			//value as in and out, for static attribute calculation
			void apply(const Owner_T& owner, const std::string& attr, int& value) const;
			
			//for passive trigger
			void react(Owner_T& owner, const std::string& event_name);

			//TODO: should be destroyed if not alive.
			//      maybe find a way later.
			[[nodiscard]] bool alive() const;

		protected:
			//TODO: rename
			virtual void apply_(const Owner_T& owner, const std::string& attr, int& value) const;

			//TODO: rename
			//maybe input Event not string
			//returns alive
			virtual bool react_(Owner_T& owner, const std::string& event_name);

		private:
			bool alive_;
		};

		template<typename Owner_T>
		class SimpleStatusEffect :public StatusEffect<Owner_T>{
		public:
			using ApplyFunc = std::function<void(const Owner_T&, const std::string& attr, int& value)>;
			using ApplyMap = std::map<std::string, ApplyFunc>;

			using ReactFunc = std::function<bool(Owner_T&, const std::string& event_name)>;
			using ReactMap = std::map<std::string, ReactFunc>;

			SimpleStatusEffect(const ApplyMap& apply_map, const ReactMap& react_map);

		protected:
			void apply_(const Owner_T& owner, const std::string& attr, int& value) const override;
			bool react_(Owner_T& owner, const std::string& event_name) override;

		private:
			ApplyMap apply_map_;
			ReactMap react_map_;
		};

	}
}

#include "StatusEffect.cpp"