#pragma once
#include "../command.h"
#include "../../phase/skipPhase.h"
namespace commands
{

class Skip : public Command // inheritance from base class
{
public:
	Skip(phase::SkipPhase* ph);
	void Execute(Context* ctx) override;
private:
	phase::SkipPhase* phase;
};

}
