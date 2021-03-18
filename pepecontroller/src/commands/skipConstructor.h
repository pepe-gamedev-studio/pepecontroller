#pragma once
#include "commandConstructor.h"

#include <memory>
namespace commands
{
	class SkipPhase;
class SkipConstructor : public CommandConstructor // inheritance from base class
{
public:
	SkipConstructor(SkipPhase* ph);
	std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
private:
	SkipPhase* phase;
};

}
