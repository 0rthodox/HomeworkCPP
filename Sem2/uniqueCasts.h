#pragma once

#ifndef _UNIQUE_CASTS_
#define _UNIQUE_CASTS_

#include <memory>

#define NODISCARD [[nodiscard]]

template <typename Dst, typename Src>
NODISCARD std::unique_ptr<Dst> static_pointer_cast(std::unique_ptr<Src>& sourcePointer) {
	const auto convertedPtr = static_cast<typename std::unique_ptr<Dst>::element_type*>(sourcePointer.release());
	return std::unique_ptr<Dst>(convertedPtr, sourcePointer.get_deleter());
}

template <typename Dst, typename Src>
NODISCARD std::unique_ptr<Dst> dynamic_pointer_cast(std::unique_ptr<Src>& sourcePointer) {
	const auto convertedPtr = dynamic_cast<typename std::unique_ptr<Dst>::element_type*>(sourcePointer.release());
	if (convertedPtr) {
		return std::unique_ptr<Dst>(convertedPtr);
	} else {
		return std::unique_ptr<Dst>();
	}
}

template <typename Dst, typename Src>
NODISCARD std::unique_ptr<Dst> const_pointer_cast(std::unique_ptr<Src>& sourcePointer) {
	const auto convertedPtr = const_cast<typename std::unique_ptr<Dst>::element_type*>(sourcePointer.release());
	return std::unique_ptr<Dst>(convertedPtr, sourcePointer.get_deleter());
}

template <typename Dst, typename Src>
NODISCARD std::unique_ptr<Dst> reinterpret_pointer_cast(std::unique_ptr<Src>& sourcePointer) {
	const auto convertedPtr = reinterpret_cast<typename std::unique_ptr<Dst>::element_type*>(sourcePointer.release());
	return std::unique_ptr<Dst>(convertedPtr, sourcePointer.get_deleter());
}

#endif _UNIQUE_CASTS_
