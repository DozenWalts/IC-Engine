#ifndef __THREAD_H__
#define __THREAD_H__

#ifdef _WIN32
	#include <windows.h>
	#include <intrin.h>
#else
	//if _LINUX
	#include <pthread.h>
#endif

#include "BaseTypes.h"
//https://developer.unigine.com/en/docs/future/migration/migration_api
//Added a set of atomic functions: AtomicCAS(), AtomicAdd(), AtomicSet(), and AtomicGet().
//Implemented exponential backoff mechanism for the SpinLock reducing the impact on CPU performance.
//Added a new Mutex class representing a simple mutex, based on atomic CAS and wrapping volatile int.
//AtomicLock operating with volatile int was replaced with the ScopedLock, based on the new simple mutex (Mutex).
//Added an RWMutex with write-preferred locking along with a couple of scoped locks for it (ScopedReaderLock and ScopedWriterLock).
//Added a new Atomic<T> class enabling to read and write the value atomically.
//Added a new ReentrantMutex, enabling a mutex to be locked multiple times by the same thread, without causing a deadlock along with a ScopedReentrantLock for it.

struct ThreadedClass{
	ThreadedClass();
	virtual ~ThreadedClass();
		
	int run(size_t size = 0x100000);
	int signal();
	int terminate();
		
	int isRunning() const;
	int isWaiting() const;
		
	virtual void process() = 0;
		
	void usleep(unsigned int usec);
	void wait();
		
	#ifdef _WIN32
		static DWORD WINAPI thread_handler(LPVOID data);
		HANDLE thread;
		HANDLE event;
	#else
		static void *thread_handler(void *data);
		pthread_t thread;
		pthread_cond_t cond;
		pthread_mutex_t mutex;
	#endif
		
	volatile int running;
	volatile int waiting;
};

//https://github.com/AlexeyAB/object_threadsafe/tree/master/contfree_shared_mutex

//Compare and swap
INLINE int AtomicCAS(volatile int *ptr,int old_value,int new_value){
	#ifdef _WIN32
		return (_InterlockedCompareExchange((long volatile*)ptr,new_value,old_value) == old_value);
	#elif __linux
		return (__sync_val_compare_and_swap(ptr,old_value,new_value) == old_value);
	#else
		if(*ptr != old_value) return 0;
		*ptr = new_value;
		return 1;
	#endif
}

INLINE void SpinLock(volatile int *ptr,int old_value,int new_value){
	while(!AtomicCAS(ptr,old_value,new_value));
}

INLINE void WaitLock(volatile int *ptr,int value){
	while(!AtomicCAS(ptr,value,value));
}

struct AtomicLock{
	INLINE AtomicLock(volatile int *ptr) : ptr(ptr) {
		SpinLock(ptr,0,1);
	}
	INLINE ~AtomicLock() {
		SpinLock(ptr,1,0);
	}
		
	volatile int *ptr;
};

#include <process.h>//_beginthreadex,_endthreadex
//--------------------------------------------------------------------------------------------------
struct ThreadFunc{// Base class for abstract thread functions
	virtual ~ThreadFunc() {}
	virtual void run() = 0;
};

template <typename T> struct ThreadFunctor : ThreadFunc{// Specialization using a functor (including free functions) with no argument
	T m_functor;
	ThreadFunctor(T functor) : m_functor(functor) {}
	virtual void run() { m_functor(); }
};

template <typename F, typename A> struct ThreadFunctorWithArg : ThreadFunc{// Specialization using a functor (including free functions) with one argument
	F m_function;
	A m_arg;
	ThreadFunctorWithArg(F function, A arg) : m_function(function), m_arg(arg) {}
	virtual void run() { m_function(m_arg); }
};

template <typename C>struct ThreadMemberFunc : ThreadFunc{// Specialization using a member function
	C *m_object;
	ThreadMemberFunc(void(C::*function)(), C *object) : m_function(function), m_object(object) {}
	virtual void run() { (m_object->*m_function)(); }
	void(C::*m_function)();
};
//--------------------------------------------------------------------------------------------------
struct Thread;

struct ThreadImpl{
	HANDLE m_thread; ///< Win32 thread handle
	unsigned int m_threadId; ///< Win32 thread identifier

	ThreadImpl(Thread* owner);
	~ThreadImpl();
	void wait();
	void terminate();
	void end();
	static unsigned int __stdcall entryPoint(void* userData);
};
//--------------------------------------------------------------------------------------------------
struct Thread{
	friend struct ThreadImpl;
	ThreadImpl *m_impl;       ///< OS-specific implementation of the thread
	ThreadFunc *m_entryPoint; ///< Abstraction of the function to run
	bool inuse;

	void run(){ m_entryPoint->run(); }
	template <typename F> Thread(F functor) :m_impl(NULL), m_entryPoint(new ThreadFunctor<F>(functor)){ inuse = false; }
	template <typename F, typename A> Thread(F function, A argument) : m_impl(NULL), m_entryPoint(new ThreadFunctorWithArg<F, A>(function, argument)){ inuse = false; }
	template <typename C> Thread(void(C::*function)(), C* object) : m_impl(NULL), m_entryPoint(new ThreadMemberFunc<C>(function, object)){ inuse = false; }
	~Thread(){ wait();delete m_entryPoint; }
	void launch(){
		inuse = true;
		wait();
		m_impl = new ThreadImpl(this);
	}
	void wait(){
		if(m_impl){
			m_impl->wait();
			delete m_impl;
			m_impl = NULL;
		};
	};
	void end(){ LOG::msg("Thread::end"); inuse = false; };
	void terminate(){
		inuse = false;
		if(m_impl){
			m_impl->terminate();
			delete m_impl;
			m_impl = NULL;
		};
	};
};
//--------------------------------------------------------------------------------------------------
/// Usage examples:
/// // ------------------example 1: non member function with one argument
/// void threadFunc(int argument){...}
/// Thread thread(&threadFunc, 5);
/// thread.launch(); // start the thread (internally calls threadFunc(5))
/// // ------------------example 2: member function
/// class Task {
///     void run(){...}
/// };
/// Task task;
/// Thread thread(&Task::run, &task);
/// thread.launch(); // start the thread (internally calls task.run())
/// // ------------------example 3: functor
/// struct Task{
///     void operator()(){...}
/// };
/// Thread thread(Task());
/// thread.launch(); // start the thread (internally calls operator() on the Task instance)

struct MutexImpl{
	CRITICAL_SECTION m_mutex; ///< Win32 handle of the mutex
	MutexImpl(){ InitializeCriticalSection(&m_mutex); }
	~MutexImpl(){ DeleteCriticalSection(&m_mutex); };
	void lock(){ EnterCriticalSection(&m_mutex); };
	void unlock(){ LeaveCriticalSection(&m_mutex); };
};

struct Mutex{
	MutexImpl *m_mutexImpl; ///< OS-specific implementation
	Mutex(){ m_mutexImpl = new MutexImpl; };
	~Mutex(){ delete m_mutexImpl; };
	void lock(){ m_mutexImpl->lock(); };
	void unlock(){ m_mutexImpl->unlock(); };
};
/// Mutex stands for "MUTual EXclusion". A mutex is a
/// synchronization object, used when multiple threads are involved.
///
/// When you want to protect a part of the code from being accessed
/// simultaneously by multiple threads, you typically use a
/// mutex. When a thread is locked by a mutex, any other thread
/// trying to lock it will be blocked until the mutex is released
/// by the thread that locked it. This way, you can allow only
/// one thread at a time to access a critical region of your code.
///
/// Usage example:
/// Database database; // this is a critical resource that needs some protection
/// Mutex mutex;
/// void thread1(){
///     mutex.lock(); // this call will block the thread if the mutex is already locked by thread2
///     database.write(...);
///     mutex.unlock(); // if thread2 was waiting, it will now be unblocked
/// }
/// 
/// void thread2(){
///     mutex.lock(); // this call will block the thread if the mutex is already locked by thread1
///     database.write(...);
///     mutex.unlock(); // if thread1 was waiting, it will now be unblocked
/// }


#endif
