#include "MyClassWorker.h"

MyClassWorker::MyClassWorker()
{
};
MyClassWorker::~MyClassWorker()
{
	if (temp != nullptr)
		delete temp;
};
void MyClassWorker::initialize(const toml::value& data_) 
{
	data = data_;
};
void MyClassWorker::processSum()
{
	qDebug() << "current thread ID : " << QThread::currentThreadId();
	if (data.size() > 0)
	{
		temp = new SumDataBase(toml::find<QVector<int> >(data, "database", "numbers"),
			toml::find<int>(data, "database", "pause"));
	}
	else
	{
		emit finished(QVector<int>(0));
		return;
	}

	qDebug() << "finish the work and sent the resultReady signal\n";
	emit finished(temp->GetSumData());
	return;
};
