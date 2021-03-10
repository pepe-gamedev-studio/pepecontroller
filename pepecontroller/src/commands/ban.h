#pragma once
#include "command.h"

#include "../storage/SqliteStorage.h"
#include "../peka2tv/peka2tvHttpClient.h"

#include <string>

namespace commands
{

class Ban : public Command // inheritance from base class
{
public:
	Ban(const std::string& name);
	void Execute(Context* ctx) override;
private:
	std::string name;
};

}
