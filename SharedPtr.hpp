#include <memory>

template <typename Resource>
class WeakPtr;

template <typename Resource>
class SharedPtr
{
	Resource* data;
	size_t* useCount;

public:
	SharedPtr() : data(nullptr), useCount(nullptr) {}

	// it's a ctor, we can't initialize existing sharedptr with resource
	SharedPtr(Resource* res) : data(res), useCount(new size_t(1)) {}

	// pass shared ptr to  create another shared ptr. if it's empty, skip, if not, increment count
	SharedPtr(const SharedPtr<Resource>& rhs) : data(rhs.data), useCount(rhs.useCount)
	{
		if (useCount)
		{
			(*useCount)++;
		}
	}

	SharedPtr(const WeakPtr <Resource>& rhs) : data(rhs.data), useCount(rhs.useCount)
	{
		if (useCount)
		{
			(*useCount)++;
		}
	}

	SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs)
	{
		if (this != &rhs)
		{
			Reset();
			data = rhs.data;
			useCount = rhs.useCount;
			if (useCount)
			{
				(*useCount)++;
			}
		}
		return *this;
	}

	~SharedPtr()
	{
		Reset();
	}

	void Reset()
	{
		if (useCount)
		{
			(*useCount)--;
			if (*useCount == 0)
			{
				delete data;
				delete useCount;
			}
		}
		data = nullptr;
		useCount = nullptr;
	}

	void Reset(Resource* res)
	{
		Reset();
		data = res;
		useCount = new size_t(1);
	}

	void Swap(SharedPtr<Resource>& rhs)
	{
		std::swap(data, rhs.data);
		std::swap(useCount, rhs.useCount);
	}

	Resource* Get() const
	{
		return data;
	}

	Resource& operator*() const
	{
		return *data;
	}

	Resource* operator->() const
	{
		return data;
	}

	size_t UseCount() const
	{
		return useCount ? *useCount : 0;
	}
};

