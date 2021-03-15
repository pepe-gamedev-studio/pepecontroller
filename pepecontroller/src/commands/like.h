#pragma once
#include "command.h"

namespace commands
{

	class Like : public Command // inheritance from base class
	{
	public:
		Like();
		void Execute(Context* ctx) override;
	};

}