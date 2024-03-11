#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include "SharedPtr.h"

template <typename Resource>
class WeakPtr
{
	Resource* data;
	size_t* refCount;
	size_t* weakCount;

public:
	WeakPtr() : data(nullptr), refCount(nullptr), weakCount(nullptr) {}

	WeakPtr(const WeakPtr<Resource>& rhs) : data(rhs.data), refCount(rhs.refCount);

	WeakPtr(const SharedPtr<Resource>& rhs) : data(rhs.data), refCount(rhs.refCount), weakCount(rhs.weakCount);

	WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs);

	WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs);
	~WeakPtr();

	void Reset();

	void Swap(WeakPtr<Resource>& rhs);

	size_t UseCount() const;

	bool Expired() const;

	SharedPtr<Resource> Lock() const;
};