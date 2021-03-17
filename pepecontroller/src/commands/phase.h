#pragma once
#include "banConstructor.h"
#include "unbanConstructor.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

using user_id = uint64_t;

namespace commands 
{
	using CommandSet = std::unordered_map<std::string, std::shared_ptr<commands::CommandConstructor>>;
	class Phase
	{
	public:
		Phase();
		virtual ~Phase() = default;
		const virtual CommandSet& GetCommands() = 0;
	protected:
		CommandSet basicCommands {
		{"ban", std::make_shared<commands::BanConstructor>() },
		{"unban", std::make_shared<commands::UnbanConstructor>() },
		};
		void mergeCommands(CommandSet& cs);
	};

}