#pragma once
#include <vector>
#include <algorithm>

#ifndef _FIND_IN_VECTOR_
#define _FIND_IN_VECTOR_

template <typename Iter, typename Obj>
bool rangeRecursiveSearch(Iter itBegin, Iter itEnd, const Obj& value) {
	if (std::distance(itBegin, itEnd) > 1) {
		auto med = next(itBegin, std::distance(itBegin, itEnd) / 2);
		if (*med == value || *itBegin == value) {
			return true;
		}
		else if (*med < value) {
			return rangeRecursiveSearch(med, itEnd, value);
		}
		else if (*med > value) {
			return rangeRecursiveSearch(itBegin, med, value);
		}
	}
	return false;
}

template <typename Obj, typename Collection>
bool recursiveSearch(const Collection& data, const Obj& value) {
	if (data.back() < value || data.front() > value) {
		return false;
	}
	return rangeRecursiveSearch(data.begin(), data.end(), value);
}

template <typename Obj>
bool vectorBinarySearch(const std::vector<Obj>& data, const Obj& value) {
	if (data.back() < value || data.front() > value) {
		return false;
	}
	auto itBegin = data.begin();
	auto itEnd = data.end();
	while (std::distance(itBegin, itEnd) > 1) {
		auto med = next(itBegin, std::distance(itBegin, itEnd) / 2);
		if (*med == value || *itBegin == value) {
			return true;
		}
		else if (*med < value) {
			itBegin = med;
		}
		else if (*med > value) {
			itEnd = med;
		}
	}
	return false;
}

#endif _FIND_IN_VECTOR_