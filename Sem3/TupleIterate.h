#pragma once

#include <tuple>

template <int Current, int End, typename Function, typename... Args>
struct Iterate {
	static void iterate(const std::tuple<Args...>& tuple, Function function) {
		function(std::get<Current>(tuple));
		Iterate<Current + 1, End, Function, Args...>::iterate(tuple, function);
	}	
};

template <int End, typename Function, typename... Args>
struct Iterate<End, End, Function, Args...> {
	static void iterate(const std::tuple<Args...>& tuple, Function function) {}	
};

template <typename Function, typename... Args>
void iterateThrough(const std::tuple<Args...>& tuple, Function function) {
	Iterate<0, sizeof...(Args), Function, Args...>::iterate(tuple, function);
}

