#pragma once
#ifndef _NGM_MAP__HPP
#define _NGM_MAP__HPP
#include <map>
namespace NGM
{
	template <class T, class V>
	using Pair = std::pair<T, V>;

	template <class T, class V>
	using Map = std::map<T, V>;

	template <class T, class V>
	using Multimap = std::multimap<T, V>;
}
#endif // _NGM_MAP__HPP
