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
        std::string buf = "";
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

void Worker::ThreadsReadFile(size_t numThreads)
{
    try
    {
        WrapperThread paralelRead;
        std::recursive_mutex lock;
        //std::cout << "threadId : " << std::this_thread::get_id() << std::endl;
        std::uintmax_t size = fs::file_size(filePath);
        if (numThreads % 2 != 0)
            numThreads++;
        std::uintmax_t sizeBufTemp = size / numThreads ;
        std::fstream fileStream(filePath, std::ios::binary | std::fstream::in);
        std::uintmax_t sizeBuf = 0;
        if (fileStream.is_open())
        {
            
            for (int i = 0; sizeBuf < size; ++i)  // && !fileStream.eof()
            {
                std::string temp(sizeBufTemp, '\0');
                fileStream.seekg(sizeBuf, std::ios::beg);
                fileStream.read(&temp[0], sizeBufTemp);

                UsefulCutting(temp, sizeBufTemp);
                    
                paralelRead.Emplace_back(std::thread(&Worker::Sum, this, temp, std::ref(lock)));
                sizeBuf += sizeBufTemp;
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
            tempIterBegin = it + 1;
        }
        std::this_thread::sleep_for(std::chrono::seconds(pause));
    }
    else
        throw std::runtime_error("Can not [operators] action : " + action + " file :" + filePath);
    std::unique_lock<std::recursive_mutex > locker(lock);
    rez += temp;
};

void Worker::UsefulCutting(std::string& temp, std::uintmax_t& sizeBufTemp)
{
    if (*(temp.end() - 1) != ' ')
    {
        auto test = [&sizeBufTemp](auto val)
        {
            sizeBufTemp--;
            return val == ' ' || val == '\0';
        };
        temp.erase(std::find_if(temp.rbegin(), temp.rend(), test).base(), temp.end());
    }
};