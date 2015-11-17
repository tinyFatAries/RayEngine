//===========================================================================
// Singleton: Template class for creating single-instance global classes.
//===========================================================================

#pragma once
#include <assert.h>

template <typename T>
class Singleton
{
private:
	/* forbidden copy constructor */
	Singleton(const Singleton<T> &);

	/* forbidden operator = */
	Singleton& operator = (const Singleton<T>&);

protected:
	static T* m_pSingleton;

public:
	Singleton()
	{
		assert(m_pSingleton == nullptr);
		m_pSingleton = static_cast<T*>(this);
	}

	~Singleton()
	{
		assert(m_pSingleton);
		m_pSingleton = nullptr;
	}

	static T& getInstance()
	{
		assert(m_pSingleton);
		return *m_pSingleton;
	}

	static T* getInstancePtr()
	{
		return m_pSingleton;
	}
};

