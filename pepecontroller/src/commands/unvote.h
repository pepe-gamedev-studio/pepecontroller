#pragma once
#include "command.h"
#include "votePhase.h"
namespace commands
{
class Unvote : public Command
{
public:

	Unvote(VotePhase* ph);
	void Execute(Context* ctx) override;
private:
	VotePhase* phase;
};

}
