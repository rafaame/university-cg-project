#pragma once

#include "common.h"

template <class T> class Singleton
{

public:

	template <typename... Args> static T* getInstance(Args... args)
	{

		if (!instance_)
			instance_ = new T(std::forward<Args>(args)...);

		return instance_;

	}

	static void destroyInstance()
	{

		delete instance_;

		instance_ = nullptr;

	}

private:

	static T* instance_;

};

template <class T> T*  Singleton<T>::instance_ = nullptr;