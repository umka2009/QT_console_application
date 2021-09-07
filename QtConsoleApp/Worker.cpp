#include "Worker.h"

Worker::Worker(int pause_ = 0, const std::string& action_ = "") : pause(pause_), rez(0), action(action_)
{
};
Worker::~Worker()
{
};


void Worker::ThreadFunction() {
    try
    {
        std::lock_guard<std::recursive_mutex> locker(g_lock);
        std::cout << "threadId : " << std::this_thread::get_id() << std::endl;
        int temp = 0;
        for (int i = 0; i < 3; ++i)
        { 
            temp = 100500 + 100500 + i;
            std::this_thread::sleep_for(std::chrono::seconds(pause));
        }        
        rez += temp;
    }
    catch (const std::exception& err)
    {
        qCritical() << "Error exception : " << err.what();
    }
    catch (...)
    {
        qCritical() << "Uncaught error exception!";
    }

};

void Worker::ThreadFunction2() {
    try
    {
        std::cout << "threadId : " << std::this_thread::get_id() << std::endl;
        int temp = 0;
        for (int i = 0; i < 3; ++i)
        {
            temp = 100500 + 100500 + i;
            std::this_thread::sleep_for(std::chrono::seconds(pause));
        }
        std::lock_guard<std::recursive_mutex> locker(g_lock);
        // сохранение резельтата
        rez += temp;
    }
    catch (const std::exception& err)
    {
        qCritical() << "Error exception : " << err.what();
    }
    catch (...)
    {
        qCritical() << "Uncaught error exception!";
    }

};

