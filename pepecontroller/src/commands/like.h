#pragma once
#include "command.h"

namespace commands
{
	class Like : public Command // inheritance from base class
	{
	public:
		void Execute(Context* ctx) override;
	private:
	};

}