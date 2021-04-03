#include "skipConstructor.h"
#include "../command/skip.h"
namespace commands
{

SkipConstructor::SkipConstructor(phase::MoviePhase* ph) : phase(ph) {};

std::unique_ptr<Command> SkipConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
{
	return std::make_unique<Skip>(phase);
}

}