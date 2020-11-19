#include "voteConstructor.h"
#include "vote.h"

#include <sstream>
#include <limits>

namespace commands
{
std::unique_ptr<Command> VoteConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
{
	std::stringstream ss(msg.text);
	ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

	uint32_t num;
	ss >> num;

	return std::make_unique<Vote>(num);
}

}