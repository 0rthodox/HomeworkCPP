#pragma once

#include <functional>
#include <type_traits>
#include <cstdint>
#include <sstream>
#include <iomanip>

template<typename F>
struct hashFloating : std::_Conditionally_enabled_hash<F, std::is_floating_point<F>::value>  {
	constexpr static int _DIGITS = 15;
	[[nodiscard]] size_t operator()(F value) {
		intmax_t integral, fractional;
		std::stringstream temporaryStream;
		temporaryStream << std::setprecision(_DIGITS) << value;
		temporaryStream >> fractional;
		temporaryStream.ignore(1);
		temporaryStream >> integral;
		std::hash<intmax_t> hash;
		return std::bit_xor()(hash(fractional), hash(integral));
	}
};

template <typename F>
struct fastHashFloating : std::_Conditionally_enabled_hash<F, std::is_floating_point<F>::value> {
	
};
template<>
struct fastHashFloating<double> {
	[[nodiscard]] size_t operator()(double value) {
		std::hash<long> hashFunction;
		long* pointerLong = reinterpret_cast<long*>(&value);
		return hashFunction(*pointerLong);
	}
};
template<>
struct fastHashFloating<float> {
	[[nodiscard]] size_t operator()(float value) {
		std::hash<int> hashFunction;
		int* pointerInt = reinterpret_cast<int*>(&value);
		return hashFunction(*pointerInt);
	}
};