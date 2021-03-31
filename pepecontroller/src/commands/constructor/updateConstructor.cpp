#include "updateConstructor.h"
#include "../command/update.h"

#include <string>
#include <sstream>

namespace commands
{

	std::unique_ptr<Command> UpdateConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
	{
			std::stringstream ss(msg.text);
			ss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // ignore text before space

			std::string arg;
			ss >> arg;
			return std::make_unique<Update>(arg);
	}

}