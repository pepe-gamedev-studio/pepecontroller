#pragma once
#include "command.h"

#include <cstdint>

namespace commands
{

class Vote : public Command
{
public:
	Vote(uint32_t num);
	void Execute(Context* ctx) override;
private:
	uint32_t num;
};

}
