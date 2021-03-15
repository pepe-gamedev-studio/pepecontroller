#include "dislikeConstructor.h"
#include "dislike.h"
namespace commands
{
	std::unique_ptr<Command> DislikeConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
	{
		return std::make_unique<Dislike>();
	}
}