#pragma once
#include "command.h"
#include "phase.h"
#include <unordered_set>
#include <cstdint>

namespace commands
{
class Vote : public Command
{
public:
	//void resetCache();
	/*Vote(uint32_t num);*/
	Vote(VotePhase* ph, uint8_t num);
	void Execute(Context* ctx) override;
private:
	VotePhase* phase;
	uint8_t num;
	//std::unordered_set<size_t> voteCache;
};

}
