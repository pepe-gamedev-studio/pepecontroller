#pragma once
#include "../command.h"

namespace commands
{

	class Dislike : public Command // inheritance from base class
	{
	public:
		Dislike(const int64_t);
		Dislike();
		void Execute(Context* ctx) override;
	private:
		std::optional<int64_t> movieID;
	};

}