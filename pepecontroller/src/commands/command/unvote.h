#pragma once
#include "../command.h"
#include "../../phase/votePhase.h"
namespace commands
{
class Unvote : public Command
{
public:
	Unvote(phase::VotePhase* ph);
	void Execute(Context* ctx) override;
private:
	phase::VotePhase* phase;
};

}
