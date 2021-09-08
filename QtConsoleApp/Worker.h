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
#include <filesystem>
#include <regex>
#include "WrapperThread.h"

namespace fs = std::filesystem;

class Worker
{
public:

	Worker(int pause_, const std::string& action, const std::string& filePath_);
	~Worker();

	// parallel execution
	void ThreadFunction();
	void ThreadsReadFile(size_t numThreads);
	void Sum(std::string_view buf, std::recursive_mutex& lock);  // std::string_view
	int Getrez() const { return rez; };
	// std::recursive_mutex lock;
private:
	void UsefulCutting(std::string& temp, std::uintmax_t& sizeBufTemp);
	int pause;
	int rez = 0;
	std::string action;
	std::string filePath;

};

#endif // !WORKER_H
