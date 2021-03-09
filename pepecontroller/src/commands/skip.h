#pragma once
#include "command.h"

namespace commands
{

class Skip : public Command // inheritance from base class
{
public:
	Skip();
	void Execute(Context* ctx) override;
};

}
