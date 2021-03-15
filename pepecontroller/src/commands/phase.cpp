#include "phase.h"
namespace commands
{

Phase::Phase()
{
}
void Phase::mergeCommands(CommandSet& cs)
{
	cs.insert(basicCommands.begin(), basicCommands.end());
}




VotePhase::VotePhase()
{
	mergeCommands(this->voteCommands);
}
const Phase::CommandSet& VotePhase::GetCommands()
{
	return this->voteCommands;
}
void VotePhase::Vote(user_id user, uint8_t num)
{
	
}




SkipPhase::SkipPhase()
{
	mergeCommands(this->skipCommands);
}
const Phase::CommandSet& SkipPhase::GetCommands()
{
	return this->skipCommands;
}





MoviePhase::MoviePhase()
{
	mergeCommands(this->movieCommands);
}
const Phase::CommandSet& MoviePhase::GetCommands()
{
	return this->movieCommands;
}

}