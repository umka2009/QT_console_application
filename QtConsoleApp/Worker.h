#pragma once

#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <mutex>
#include <QtCore/QCoreApplication>

class Worker
{
public:

	Worker(int pause_,const std::string& action, const std::string& filePath);
	~Worker();

	// parallel execution
	void ThreadFunction();
	int Getrez() const { return rez; };
private:
	int pause;
	int rez = 0;
	std::string action;
	std::string filePath;
};

#endif // !WORKER_H
