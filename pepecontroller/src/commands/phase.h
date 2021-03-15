#pragma once
#include "Constructors.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

typedef uint64_t user_id;

namespace commands 
{
	class Phase
	{
	public:
		Phase();
		virtual ~Phase() = default;
		using CommandSet = std::unordered_map<std::string, std::shared_ptr<commands::CommandConstructor>>;
		const virtual CommandSet& GetCommands() = 0;
	protected:
		CommandSet basicCommands {
		{"ban", std::make_shared<commands::BanConstructor>() },
		{"unban", std::make_shared<commands::UnbanConstructor>() },
		};
		void mergeCommands(CommandSet& cs);
		template <typename T, typename std::enable_if<std::is_base_of<Phase, T>::value, bool>::type = true> void SetPhase();
	};

}