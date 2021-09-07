#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <QtCore/QCoreApplication>

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <thread>
#include <CLI.hpp>
#include <toml.hpp>
#include <exception>
#include <QTextStream>
#include "Worker.h"
#include "WrapperThread.h"

std::string GetDescription();
bool CheckCommandArgument(int& argc,char* argv1[], std::string& fileName);
void PrintSum(const std::vector<Worker>& temp);

#endif // !MAIN_H