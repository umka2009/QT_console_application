#include "WrapperThread.h"

WrapperThread::WrapperThread()
{

};
WrapperThread::~WrapperThread()
{
	for (int i = 0; i < myThread.size(); ++i)
	{
		if (myThread[i].joinable())
			myThread[i].join();
	}
	myThread.clear();
};
void WrapperThread::Emplace_back(std::thread&& thread_)
{
	myThread.emplace_back(std::move(thread_));
};
size_t WrapperThread::Size() const
{
	return myThread.size();
};
const std::thread& WrapperThread::operator[] (size_t it) const
{
	return myThread[it];
};