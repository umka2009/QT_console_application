#pragma once

#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <vector>
#include <iostream>
#include <chrono>
#include <mutex>
#include <QtCore/QCoreApplication>

class Worker
{
public:

	Worker(int pause_);
	~Worker();
	// ���������������� ���������� 
	void ThreadFunction();
	// ����������� ����������
	void ThreadFunction2();
	int Getrez() const { return rez; };
private:
	std::recursive_mutex g_lock;
	int pause;
	int rez;
};

#endif // !WORKER_H
