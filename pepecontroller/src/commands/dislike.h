#pragma once
#include "command.h"

namespace commands
{

	class Dislike : public Command // inheritance from base class
	{
	public:
		Dislike();
		void Execute(Context* ctx) override;
	};

}