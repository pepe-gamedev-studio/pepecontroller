#pragma once
#include "command.h"
#include "skipPhase.h"
namespace commands
{

class Skip : public Command // inheritance from base class
{
public:
	Skip(SkipPhase* ph);
	void Execute(Context* ctx) override;
private:
	SkipPhase* phase;
};

}
