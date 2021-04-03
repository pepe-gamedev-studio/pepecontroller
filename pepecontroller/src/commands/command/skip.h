#pragma once
#include "../command.h"
#include "../../phase/moviePhase.h"
namespace commands
{

class Skip : public Command // inheritance from base class
{
public:
	Skip(phase::MoviePhase* ph);
	void Execute(Context* ctx) override;
private:
	phase::MoviePhase* phase;
};

}
