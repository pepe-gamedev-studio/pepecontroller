#include "banConstructor.h"
#include "../command/ban.h"

#include <string>
#include <sstream>

namespace commands
{

std::unique_ptr<Command> BanConstructor::Construct(const peka2tv::Peka2tvSIOClient::ChatMessage& msg)
{
	std::stringstream ss(msg.text);
	ss.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // ignore text before space

	std::string name;
	ss >> name;

	return std::make_unique<Ban>(name);
}


}
