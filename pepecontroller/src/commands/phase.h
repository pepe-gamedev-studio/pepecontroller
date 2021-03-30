#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include "commandConstructor.h"

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
		CommandSet basicCommands;
		void mergeCommands(CommandSet& cs);
	};

}