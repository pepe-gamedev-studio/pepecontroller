#include "likeConstructor.h"
#include "like.h"

namespace commands
{
	std::unique_ptr<Command> LikeConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
	{
		return std::make_unique<Like>();
	}
}