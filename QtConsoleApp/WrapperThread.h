#pragma once

#ifndef WRAPPERTHREAD_H
#define	WRAPPERTHREAD_H

#include <vector>
#include <thread>

class WrapperThread
{
public:
	WrapperThread();
	~WrapperThread();
	void Emplace_back(std::thread&& thread_);
	size_t Size() const;
	const std::thread& operator[] (size_t it) const;

	 WrapperThread(const WrapperThread& tmpThread) = delete;
	 WrapperThread& operator=(const WrapperThread& tmpThread) = delete;

private:
	std::vector<std::thread> myThread = {};
};

#endif // !WRAPPERTHREAD_H

