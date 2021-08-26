#include "SumDataBase.h"

SumDataBase::SumDataBase(QVector<int> numbers_, int sleep_)
	: numbers(numbers_), sleep(sleep) 
{
};
SumDataBase::~SumDataBase() 
{
};

QVector<int> SumDataBase::GetSumData()
{
	QTextStream out(stdout);
	for (auto it = numbers.begin(); it != numbers.end(); ++it)
	{
		*it += *it;
		out << *it << " ";
		sleepMs(sleep);
	}
	return numbers;
};
void SumDataBase::sleepMs(int ms)
{
	static QMutex mutex;
	static QMutexLocker locker(&mutex);
	mutex.tryLock(ms);
};