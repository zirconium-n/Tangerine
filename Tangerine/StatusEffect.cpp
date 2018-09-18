#pragma once
#include "StatusEffect.h"

namespace sgk {
	namespace tangerine {
		template<typename Owner_T>
		StatusEffect<Owner_T>::StatusEffect():
			alive_(true)
		{}

		template<typename Owner_T>
		void StatusEffect<Owner_T>::apply(const Owner_T & owner, const std::string & attr, int & value) const{
			if (!alive()) {
				return;
			}
			apply_(owner, attr, value);
			return;
		}

		template<typename Owner_T>
		void StatusEffect<Owner_T>::react(Owner_T & owner, const std::string & event_name){
			if (!alive()) {
				return;
			}
			alive_ = react_(owner, event_name);
			return;
		}

		template<typename Owner_T>
		bool StatusEffect<Owner_T>::alive() const{
			return alive_;
		}

		template<typename Owner_T>
		void StatusEffect<Owner_T>::apply_(const Owner_T & owner, const std::string & attr, int & value) const{
			return;
		}

		template<typename Owner_T>
		bool StatusEffect<Owner_T>::react_(Owner_T & owner, const std::string & event_name){
			return true;
		}


		template<typename Owner_T>
		SimpleStatusEffect<Owner_T>::SimpleStatusEffect(const ApplyMap & apply_map, const ReactMap & react_map) :
			apply_map_(apply_map),
			react_map_(react_map)
		{}

		template<typename Owner_T>
		void SimpleStatusEffect<Owner_T>::apply_(const Owner_T & owner, const std::string & attr, int & value) const{
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