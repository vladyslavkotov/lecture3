#include <iostream>
#include <stdexcept>
#include <utility>

template <typename Resource>
class SharedPtr;

template <typename Resource>
class WeakPtr
{
	Resource* data;
	size_t* useCount;
	size_t* weakCount;

public:
	WeakPtr() : data(nullptr), useCount(nullptr), weakCount(nullptr) {}

	explicit WeakPtr(const WeakPtr<Resource>& rhs) : data(rhs.data), useCount(rhs.useCount), weakCount(rhs.weakCount)
	{
		if (weakCount)
		{
			(*weakCount)++;
		}
	}

	WeakPtr(const SharedPtr<Resource>& rhs) : data(rhs.data), useCount(rhs.useCount)
	{
		if (weakCount)
		{
			(*weakCount)++;
		}
	}

	WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs)
	{
		if (this != &rhs)
		{
			Reset();
			data = rhs.data;
			useCount = rhs.useCount;
			weakCount = rhs.weakCount;
			if (weakCount)
			{
				(*weakCount)++;
			}
		}
		return *this;
	};

	WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs)
	{
		if (this != &rhs)
		{
			Reset();
			data = rhs.data;
			useCount = rhs.useCount;
			if (useCount)
			{
				weakCount = new size_t(1);
			}
		}
		return *this;
	}

	~WeakPtr()
	{
		Reset();
	}

	void Reset()
	{
		if (weakCount && *weakCount > 0)
		{
			(*weakCount)--;
			if (*weakCount == 0)
			{
				delete data;
				delete useCount;
				delete weakCount;
			}
			data = nullptr;
			useCount = nullptr;
			weakCount = nullptr;
		}
	}

	void Swap(WeakPtr<Resource>& rhs)
	{
		std::swap(data, rhs.data);
		std::swap(useCount, rhs.useCount);
		std::swap(weakCount, rhs.weakCount);
	}

	size_t UseCount() const
	{
		return useCount? *useCount : 0;
	}

	bool Expired() const
	{
		return useCount ? *useCount == 0 : true;
	}

	SharedPtr<Resource> Lock() const
	{
		return Expired() ? SharedPtr<Resource>() : SharedPtr<Resource>(*this);
	};
};