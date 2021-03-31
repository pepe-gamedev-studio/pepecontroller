#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include "../commands/commandConstructor.h"

using user_id = uint64_t;

namespace phase
{
	struct CmdConstructor
	{
		std::shared_ptr<commands::CommandConstructor> cmdConst;
		uint8_t cmdGroup; // required userGroup to do the command
	};

	using CommandSet = std::unordered_map<std::string, CmdConstructor>;
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