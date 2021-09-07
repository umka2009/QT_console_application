#include "Worker.h"

Worker::Worker(int pause_ = 0, const std::string& action_ = "", const std::string& filePath_ = "testNumber.conf") 
    : pause(pause_), rez(0), action(action_), filePath(filePath_)
{
};
Worker::~Worker()
{
};

void Worker::ThreadFunction() {
    try
    {
        //std::cout << "threadId : " << std::this_thread::get_id() << std::endl;
        std::basic_fstream<unsigned char> fileStream(filePath, std::ios::binary | std::fstream::in);
        if (!fileStream.is_open())
        {
            throw std::runtime_error("Can not open file " + filePath);
        }

        auto tempIterEnd = std::istreambuf_iterator<unsigned char>();
        auto tempIter = std::istreambuf_iterator<unsigned char>(fileStream);
        int temp = 0;
        auto tempIterBegin = tempIter;
        auto findSpace = [&tempIterBegin](auto val)
        {
            tempIterBegin++;
            return val == ' ';
        };
        while (auto it = (std::find_if(tempIter , tempIterEnd, findSpace)) != tempIterEnd)
        {
            if (action == "+")
            {
                temp += std::stoi(std::string(tempIterBegin, tempIter));
                tempIterBegin = tempIter;
                std::this_thread::sleep_for(std::chrono::seconds(pause));
            }
            else
                throw std::runtime_error("Can not [operators] action : " + action + " file :" + filePath);
        }
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

