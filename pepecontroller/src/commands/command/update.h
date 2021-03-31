#pragma once
#include "../command.h"
#include <string>

namespace commands
{

	class Update : public Command // inheritance from base class
	{
	public:
		Update(const std::string& arg);
		void Execute(Context* ctx) override;
	private:
		std::string arg;
	};

}