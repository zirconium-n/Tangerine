#pragma once
#include <map>
#include <string>
#include <functional>

namespace sgk {
	namespace general {
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
			virtual void apply_(const Owner_T& owner, const std::string& attr, int& value) const;

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

namespace sgk {
	namespace general {
		template<typename Owner_T>
		StatusEffect<Owner_T>::StatusEffect() :
			alive_(true)
		{}

		template<typename Owner_T>
		void StatusEffect<Owner_T>::apply(const Owner_T & owner, const std::string & attr, int & value) const {
			if (!alive()) {
				return;
			}
			apply_(owner, attr, value);
			return;
		}

		template<typename Owner_T>
		void StatusEffect<Owner_T>::react(Owner_T & owner, const std::string & event_name) {
			if (!alive()) {
				return;
			}
			alive_ = react_(owner, event_name);
			return;
		}

		template<typename Owner_T>
		bool StatusEffect<Owner_T>::alive() const {
			return alive_;
		}

		template<typename Owner_T>
		void StatusEffect<Owner_T>::apply_(const Owner_T & owner, const std::string & attr, int & value) const {
			return;
		}

		template<typename Owner_T>
		bool StatusEffect<Owner_T>::react_(Owner_T & owner, const std::string & event_name) {
			return true;
		}


		template<typename Owner_T>
		SimpleStatusEffect<Owner_T>::SimpleStatusEffect(const ApplyMap & apply_map, const ReactMap & react_map) :
			apply_map_(apply_map),
			react_map_(react_map)
		{}

		template<typename Owner_T>
		void SimpleStatusEffect<Owner_T>::apply_(const Owner_T & owner, const std::string & attr, int & value) const {
			auto iter = apply_map_.find(attr);
			if (iter == apply_map_.end())
				return;

			iter->second(owner, attr, value);
			return;
		}

		template<typename Owner_T>
		bool SimpleStatusEffect<Owner_T>::react_(Owner_T & owner, const std::string & event_name)
		{
			auto iter = react_map_.find(event_name);
			if (iter == react_map_.end()) {
				return true;
			}
			return iter->second(owner, event_name);
		}
	}
}