#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include "Constructors.h"
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

	class VotePhase : public Phase
	{
	public:
		VotePhase();
		const CommandSet& GetCommands() override;
		void Vote(user_id user, uint8_t num);
		uint8_t result();
	private:
		CommandSet voteCommands
		{
			{"vote", std::make_shared<commands::VoteConstructor>() },
		};
		std::unordered_set<user_id> VoteCache;

	};

	class SkipPhase : public Phase
	{
	public:
		SkipPhase();
		const CommandSet& GetCommands() override;
	private:
		CommandSet skipCommands
		{
			{"skip", std::make_shared<commands::SkipConstructor>() },
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		};
	};

	class MoviePhase : public Phase
	{
	public:
		MoviePhase();
		const CommandSet& GetCommands() override;
	private:
		CommandSet movieCommands
		{
			{"like", std::make_shared<commands::LikeConstructor>() },
			{"dislike", std::make_shared<commands::DislikeConstructor>() },
		};
	};
	
}