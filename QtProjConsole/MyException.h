#pragma once

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <QException>
// #include <QtConcurrent>
class MyException : public QException
{
public:

    MyException(const QString& message_);

    virtual ~MyException() {};

    void raise() const override ;

    MyException* clone() const override ;

    QString Get() const;

    void operator=(const MyException&) = delete;

private:
    QString message;
};

#endif // !MYEXCEPTION_H