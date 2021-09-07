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
        auto tempIterBegin = std::istreambuf_iterator<unsigned char>(fileStream);
        int temp = 0;
        std::string buf;
        auto findSpace = [&buf](auto val)
        {
            if(val != ' ')
                buf += val;     
            return val == ' ';
        };
        for (auto it = std::find_if(tempIterBegin, tempIterEnd, findSpace); it != tempIterEnd; it = (std::find_if(tempIterBegin, tempIterEnd, findSpace)))
        {
            if (action == "+")
            {
                temp += std::stoi(buf);
                tempIterBegin = it;
                tempIterBegin++;
                buf.clear();
                std::this_thread::sleep_for(std::chrono::seconds(pause));
            }
            else
                throw std::runtime_error("Can not [operators] action : " + action + " file :" + filePath);
        }
        // сохранение резельтата
        rez = temp;
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

void Worker::ThreadsReadFile(int sizeBuf, int numThreads)
{
    try
    {
        
        WrapperThread paralelRead;
        std::recursive_mutex lock;
        //std::cout << "threadId : " << std::this_thread::get_id() << std::endl;
        std::uintmax_t size = fs::file_size(filePath) / 2;
        std::uintmax_t sizeBufTemp = (size / numThreads <= sizeBuf) ? sizeBuf : size / numThreads ;
        std::ifstream fileStream(filePath, std::ios::binary | std::fstream::in);

        if (fileStream.is_open())
        {
            std::string temp(sizeBufTemp, '\0');
            while (fileStream && !fileStream.eof())
            {
                fileStream.getline(&temp[0], sizeBufTemp, '\0');
                paralelRead.Emplace_back(std::thread(&Worker::Sum, this, temp, std::ref(lock)));
            }
        }
        else
            throw std::runtime_error("Can not open file " + filePath);
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

void Worker::Sum(std::string_view buf, std::recursive_mutex& lock)
{
    int temp = 0;
    auto tempIterEnd = buf.end();
    auto tempIterBegin = buf.begin();

    if (action == "+")
    {
        auto findSpace = [](auto val)
        {
            return val == ' ';
        };
        for (auto it = std::find_if(tempIterBegin, tempIterEnd, findSpace); it != tempIterEnd; it = (std::find_if(tempIterBegin, tempIterEnd, findSpace)))
        {
            std::string tempBuf(tempIterBegin, it);
            std::regex reg("^[0-9]{1,10}$");
            if (std::regex_match(tempBuf, reg))
                temp += std::stoi(tempBuf);
            tempIterBegin = it;
            tempIterBegin++;
            std::this_thread::sleep_for(std::chrono::seconds(pause));
        }
    }
    else
        throw std::runtime_error("Can not [operators] action : " + action + " file :" + filePath);
    std::unique_lock<std::recursive_mutex > locker(lock);
    rez += temp;
};