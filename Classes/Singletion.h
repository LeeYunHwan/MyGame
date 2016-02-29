#pragma once

template<typename T>
class Singleton
{
private:
	static T* m_pInstance;

protected:
	Singleton() {}
	virtual ~Singleton() {}
	Singleton(const Singleton& s) {}

private:
	static void destroy()
	{
		if (m_pInstance != nullptr)
			delete m_pInstance;
	}

public:
	static T* getInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T;

		return m_pInstance;
	}
};

template<typename T>T* Singleton<T>::m_pInstance = nullptr;