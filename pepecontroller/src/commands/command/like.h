#pragma once
#include "../command.h"

namespace commands
{
	class Like : public Command // inheritance from base class
	{
	public:
		Like(const int64_t);
		Like();
		void Execute(Context* ctx) override;
	private:
		std::optional<int64_t> movieID;
	};

}