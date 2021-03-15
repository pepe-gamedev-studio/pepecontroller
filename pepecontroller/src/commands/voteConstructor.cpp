#include "voteConstructor.h"
#include "vote.h"
#include <sstream>
#include <limits>

namespace commands
{
	VoteConstructor::VoteConstructor(VotePhase* ph) : phase(ph) {};

std::unique_ptr<Command> VoteConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
{
	std::stringstream ss(msg.text);
	ss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // ignore text before space

	uint8_t num;
	ss >> num;

	return std::make_unique<Vote>(phase, num);
}

}