#pragma once
#include "storage/models/user.h"

#include <iostream>

namespace storage::models::user
{

std::ostream& operator<<(std::ostream& os, const storage::models::user::User& x);

}