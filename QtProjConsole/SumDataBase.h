#pragma once

#ifndef SUMDATABASE_H
#define SUMDATABASE_H

#include <QVector>
#include <QMutex>
#include <QTextStream>
#include <QObject>

class SumDataBase
{
public:
	SumDataBase(QVector<int> numbers_, int sleep_);
	~SumDataBase();

	QVector<int> GetSumData();
	void sleepMs(int ms);
private:
	QVector<int> numbers;
	int sleep;
};

#endif // !SUMDATABASE_H
