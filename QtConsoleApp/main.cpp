#include "main.h"

int main(int argc, char *argv[])
{
     QCoreApplication app(argc, argv);
    try
    {
        std::string fileName = "";
        if (CheckCommandArgument(argc, argv, fileName))
        {
            const toml::value data = toml::parse(fileName);
            const auto dataProcessing = toml::find<std::vector<std::string> >(data, "database", "numbers");
            const auto pause = toml::find<int >(data, "database", "pause");
            const auto action = toml::find<std::string >(data, "operators", "action");

            std::vector<Worker> sumWorker = {};
            for (const auto& it : dataProcessing)
                sumWorker.emplace_back(pause, action, it);
            
            //WrapperThread sum;
            //for (auto& it : sumWorker)
            //    sum.Emplace_back(std::thread(&Worker::ThreadFunction, std::ref(it)));

            int sizeBuf = 1024;
            int ThreadNum = 2;
            WrapperThread sumParalelRead;
            for (auto& it : sumWorker)
                sumParalelRead.Emplace_back(std::thread(&Worker::ThreadsReadFile, std::ref(it), sizeBuf, ThreadNum));

            sumParalelRead.~WrapperThread();

            PrintSum(sumWorker);
        }
    }
    catch (const std::exception& err)
    {
        qCritical() << "Error exception : " << err.what();
    }
    catch (...)
    {
        qCritical() << "Uncaught error exception!"; 
    }

     return app.exec();
}

std::string GetDescription()
{
    std::string description;
    description += "Console application that accepts a configuration files as a parameters\n";
    description += "The files from which the application should read the parameters\n";
    description += "must be in .toml format<br> (Filename extension - .toml )\n";
    description += "The required list of files are listed separated by a space.\n";
    return description;
}

bool CheckCommandArgument(int& argc,char* argv1[], std::string& fileName)
{
    fileName = "";
    CLI::App app{ GetDescription(), "Console read .toml" };
    bool my_flag1{ false };
    app.set_help_flag("-h,--help", "Default source file to read \"nameSource.toml\".\n <-f | -d> | <--file | --default> [source] ");
    app.add_flag("-d, --default", my_flag1, "Default source file name to read \"source.toml\",\nignore option [-f], [--file] .")->take_last();
    app.add_option("-f, --file", fileName, "Source file to read \"nameSource.toml\".")->take_last()->check(CLI::ExistingPath);

    CLI11_PARSE(app, argc, argv1);
    if (my_flag1)
    {
        auto path_result = CLI::detail::check_path("source.toml");
        if (path_result == CLI::detail::path_type::nonexistent) {
            throw CLI::ValidationError("File does not exist, default source : source.toml");
        }
        if (path_result == CLI::detail::path_type::directory) {
            throw CLI::ValidationError("File is actually a directory: source ");
        }
        fileName = "source.toml";
    }

    return true;
}

void PrintSum(const std::vector<Worker>& temp)
{
    size_t workerNum = 1;
    for (auto it = temp.begin(); it != temp.end(); ++it)
        std::cout << "Worker : "<< (workerNum++) << " Sum from file : " << it->Getrez() << std::endl;
};