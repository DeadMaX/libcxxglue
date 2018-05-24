#ifndef _LIBCXXGLUE_MUTEX_H_
#define _LIBCXXGLUE_MUTEX_H_

namespace libcxxglue
{

class RWMutex
{
	public:
		void rlock();
		void wlock();
		void unlock();
};


} // namespace libcxxglue


// pthread emulation
using pthread_rwlock_t = libcxxglue::RWMutex;
inline pthread_rwlock_t PTHREAD_RWLOCK_INITIALIZER = pthread_rwlock_t{};

static inline int pthread_rwlock_rdlock(pthread_rwlock_t *__lock)
{
	__lock->rlock();
	return 0;
}

static inline int pthread_rwlock_unlock(pthread_rwlock_t *__lock)
{
	__lock->unlock();
	return 0;
}

static inline int pthread_rwlock_wrlock(pthread_rwlock_t *__lock)
{
	__lock->wlock();
	return 0;
}

#endif
