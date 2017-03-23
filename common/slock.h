#ifndef _SLOCK_H_
#define _SLOCK_H_
#include <pthread.h>

class ILock
{
public:
	ILock() {};
	virtual ~ILock() {};
	virtual void Lock() const = 0;
	virtual void Unlock() const = 0;
};

class IMutex : public ILock
{
public:
	IMutex();
	virtual ~IMutex();
	virtual void Lock() const;
	virtual void Unlock() const;
private:
	mutable pthread_mutex_t m_mutex;
};

inline IMutex::IMutex()
{
	pthread_mutex_init(&m_mutex, NULL);
}

inline IMutex::~IMutex()
{
	pthread_mutex_destroy(&m_mutex);
}

inline void IMutex::Lock() const
{
	pthread_mutex_lock(&m_mutex);
}

inline void IMutex::Unlock() const
{
	pthread_mutex_unlock(&m_mutex);
}

#endif //#define _SLOCK_H_
