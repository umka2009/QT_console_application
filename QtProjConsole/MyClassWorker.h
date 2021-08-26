#pragma once

#ifndef MYCLASSWORKER_H
#define MYCLASSWORKER_H

#include <QThread>
#include <QObject>
#include <QString>
#include <QVector>
#include "SumDataBase.h"
#include <toml.hpp>
#include <QDebug>



class MyClassWorker :public QObject
{
Q_OBJECT
public:
	MyClassWorker();
	~MyClassWorker();
	void initialize(const toml::value& data_);
public slots:
	void processSum();
signals:
	void finished(const QVector<int> result);
private:
	SumDataBase* temp = nullptr;
	toml::value data;
};
// cooperative multitasking
#endif // !MYCLASSWORKER_H