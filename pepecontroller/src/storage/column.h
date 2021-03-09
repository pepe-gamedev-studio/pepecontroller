#pragma once
#include <sqlite_orm.h>

namespace storage
{

template<class O, class T, class ...Op>
using Column = sqlite_orm::internal::column_t<O, T, const T& (O::*)() const, void (O::*)(T), Op...>;

}