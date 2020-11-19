#pragma once
#include "command.h"

namespace commands
{

class Skip: public Command
{
public:
	Skip();
	void Execute(Context* ctx) override;
};

}
