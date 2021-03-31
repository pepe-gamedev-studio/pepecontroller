#include "voteConstructor.h"
#include "../../phase/votePhase.h"
#include "../command/vote.h"
#include <sstream>
#include <limits>

namespace commands
{

	VoteConstructor::VoteConstructor(phase::VotePhase* ph) : phase(ph) {};

std::unique_ptr<Command> VoteConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
{
	std::stringstream ss(msg.text);
	ss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // ignore text before space

	uint32_t num;
	ss >> num;

	return std::make_unique<Vote>(phase, num);
}

}