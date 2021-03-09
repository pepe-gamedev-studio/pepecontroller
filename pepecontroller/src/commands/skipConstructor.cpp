#include "skipConstructor.h"
#include "skip.h"
namespace commands
{

std::unique_ptr<Command> SkipConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
{
	return std::make_unique<Skip>();
}

}