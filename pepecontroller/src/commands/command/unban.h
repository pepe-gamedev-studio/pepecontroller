#pragma once
#include "../command.h"
#include "../../storage/SqliteStorage.h"
#include "../../peka2tv/peka2tvHttpClient.h"

namespace commands
{
	class Unban : public Command
	{
	public:
		Unban(const std::string& name);
		void Execute(Context* ctx) override;
	private:
		std::string name;
	};
}