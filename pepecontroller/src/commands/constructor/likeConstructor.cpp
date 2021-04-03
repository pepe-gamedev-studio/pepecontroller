#include "likeConstructor.h"
#include "../command/like.h"

namespace commands
{
	std::unique_ptr<Command> LikeConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
	{
		std::stringstream ss(msg.text);
		ss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // ignore text before space

		std::string str;
		ss >> str;

		try
		{
			auto movieID = std::stoll(str);
			return std::make_unique<Like>(movieID);
		}
		catch (const std::exception&)
		{}
		return std::make_unique<Like>();

	}
}