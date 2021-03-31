#pragma once
#include "../commandConstructor.h"

#include <memory>
namespace phase
{
	class SkipPhase;
}
namespace commands
{
class SkipConstructor : public CommandConstructor // inheritance from base class
{
public:
	SkipConstructor(phase::SkipPhase* ph);
	std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
private:
	phase::SkipPhase* phase;
};

}
