#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <qtextstream.h>
#include <qfile.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <QVector>
#include <memory>
#include <iomanip>

//#include <QList>
//#include <algorithm>


void GetCommandLine(const QCoreApplication& app, QCommandLineParser& parser);
void SetOptionsSingle(QCommandLineParser& parser);
void SetOptionsMultiple(QCommandLineParser& parser);
void CheckCommandLineArguments(const QCommandLineParser& parser, QString& optionSet, const QString& defPath);
QString GetDescription();


#endif // MAIN_H