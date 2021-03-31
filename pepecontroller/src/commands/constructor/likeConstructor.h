#pragma once
#include "../commandConstructor.h"
namespace commands
{
	class LikeConstructor : public CommandConstructor
	{
	public:
		std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
	private:
	};
}
