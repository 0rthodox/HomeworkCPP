#pragma once
#include <vector>

#ifndef _FIND_IN_VECTOR_
#define _FIND_IN_VECTOR_

#define NODISCARD [[nodiscard]]

template <typename Iter, typename Obj>
NODISCARD Iter lowerFind(Iter itBegin, Iter itEnd, const Obj& value) {
	while (std::distance(itBegin, itEnd) > 1) {
		auto med = itBegin + std::distance(itBegin, itEnd) / 2;
		if (*med <= value) {
			itBegin = med;
		}
		else if (*med >= value) {
			itEnd = med;
		}
	}
	return itBegin;
}

template <typename Obj, typename Container>
NODISCARD typename Container::iterator binarySearch(Container& data, const Obj& value) {
	return lowerFind(data.begin(), data.end(), value);
}

template <typename Obj, typename Container>
NODISCARD typename Container::const_iterator binarySearch(const Container& data, const Obj& value) {
	return lowerFind(data.begin(), data.end(), value);
}

template <typename Obj>
NODISCARD typename std::vector<Obj>::iterator vectorBinarySearch(std::vector<Obj>& data, const Obj& value) {
	return binarySearch(data, value);
}

template <typename Obj>
NODISCARD typename std::vector<Obj>::const_iterator binarySearch(const std::vector<Obj>& data, const Obj& value) {
	return binarySearch(data, value);
}

#endif _FIND_IN_VECTOR_