#ifndef __THREAD_H__
#define __THREAD_H__

#if defined(WIN32)  || defined(__WIN32__) || defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include <process.h>
#include <windows.h>
#else
#include <pthread.h>
#endif

enum State
{
	NEW,
	RUNNING,
	TERMINATED
};

class Thread
{
public:
	Thread()
	{
		m_state = NEW;
	}

	~Thread()
	{
		delete m_threadId;
	}

	bool start()
	{
		if (m_state != NEW)
		{
			return false;
		}

#if defined(WIN32)  || defined(__WIN32__) || defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
		m_threadId = (HANDLE)_beginthreadex(NULL, 0, Thread::perform, this, 0, NULL);
		if (NULL == m_threadId)
		{
			return false;
		}
#else
		if (0 != pthread_create(&m_threadId, NULL, Thread::perform, this))
		{
			return false;
		}
#endif
		m_state = RUNNING;
		return true;
	}

	virtual void run() = 0;

private:
	volatile State m_state;

#if defined(WIN32)  || defined(__WIN32__) || defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
	HANDLE	m_threadId;
	
	void setDetach()
	{
		CloseHandle(m_threadId);
	}

	static unsigned __stdcall perform(void * arg)
#else
	pthread_t	m_threadId;

	void setDetach()
	{
		pthread_detach(m_threadId);
	}

	static void* perform(void* arg)
#endif
	{
		Thread *thread = (Thread *)arg;
		thread->setDetach();
		thread->run();
		thread->m_state = TERMINATED;
		return 0;
	}
};
#endif