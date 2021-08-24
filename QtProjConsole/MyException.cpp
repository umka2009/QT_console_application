#include "MyException.h"

MyException::MyException(const QString& message_) : message(message_)
{
};

void MyException::raise() const 
{
    throw* this; 
};
MyException* MyException::clone() const
{
    return new MyException(*this); 
};
QString MyException::Get() const
{
    return message;
};