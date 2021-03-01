#pragma once
#include "commandConstructor.h"

#include <memory>

namespace commands
{

class BanConstructor: public CommandConstructor // inheritance from base class
{
public:
	std::unique_ptr<Command> Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg) override;
};

}
