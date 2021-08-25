#include "main.h"


int main(int argc, char **argv)
{
 
    try 
    {
        // throw MyException("test");
        QCoreApplication app(argc, argv);
        QTextStream out(stdout);
        QCommandLineParser parser;
        QString optionSet;
        GetCommandLine(app, parser);
        CheckCommandLineArguments(parser, optionSet, app.applicationDirPath());

        if (optionSet.size() > 0) 
        {
            const std::string fname(optionSet.toStdString());
            const toml::value data = toml::parse(fname);
            const auto title = toml::find<std::string>(data, "title");
            const auto& database = toml::find(data, "database");
            const auto numbers = toml::find<QVector<int> >(database, "numbers");
            const auto pause = toml::find<int>(database, "pause");
            const auto myanswers = toml::find<QVector<int> >(data, "database", "answers", "myanswers");

        }
        else
        {
            throw MyException("Not enough arguments");
        }

        return app.exec();
    }
    catch (const MyException& message)
    {
        qCritical() << "Error : " << message.Get();
    }
    catch (const QUnhandledException& message)
    {
        qCritical() << "Uncaught error :" << message.what();
    }
    catch (const std::runtime_error& message)
    {
        qCritical() << "runtime_error :" << message.what();
    }
    catch (const toml::exception& message)
    {
        qCritical() << "exception :" << message.what();
    }
    catch(...)
    {
        qCritical() << "Uncaught error qexception!";
    }
}

void CheckCommandLineArguments(const QCommandLineParser& parser, QString& optionSet, const QString& defPath)
{
    ValidatingArguments(parser);
    if (parser.isSet("p"))
    {
        if (parser.isSet("s") || parser.isSet("source"))
        {
            optionSet = (parser.positionalArguments()).join("");
            optionSet.replace('/', '\\');
        }
        else if (parser.isSet("d") || parser.isSet("default"))
        {
            optionSet = defPath;
            optionSet.replace('/', '\\');
            optionSet += "\\source.toml";
        }
    }
}

void ValidatingArguments(const QCommandLineParser& parser)
{
    QMap<QString, int> indexMap;
    for (auto val : parser.optionNames())
    {
        auto it = indexMap.find(val);
        if (it != indexMap.end())
            it.value()++;
        else
            indexMap.insert(val, 1);
    }
    for(auto it = indexMap.begin(); it != indexMap.end(); ++it)
        if(it.value() > 1)
            throw MyException("Duplicate arguments");
    if (indexMap.size() > 2)
        throw MyException("A lot of arguments");
    else if (indexMap.size() < 1)
        throw MyException("Not enough arguments");
}

void GetCommandLine(const QCoreApplication& app, QCommandLineParser& parser)
{
    QCoreApplication::setApplicationName("Read .tolow");

    parser.setApplicationDescription(GetDescription());
    parser.addHelpOption();

    SetOptionsSingle(parser);
    SetOptionsMultiple(parser);

    parser.addPositionalArgument("-s, --source", QCoreApplication::translate("main",
        "Source file to read \"source.toml\" | \"source.toml\"."), "[-p] [-d] | ([-s] | [--source]) <source> ");

    parser.process(app);
}

void SetOptionsSingle(QCommandLineParser& parser)
{
    parser.addOption(QCommandLineOption("p",
        QCoreApplication::translate("main", "Set this option if you need sets parameters tor the app")));
}

void SetOptionsMultiple(QCommandLineParser& parser)
{
    parser.addOption(QCommandLineOption(QStringList() << "d" << "default",
        QCoreApplication::translate("main", "Default source file to read \"source.toml\" | \"source.toml\"")));
    parser.addOption(QCommandLineOption(QStringList() << "s" << "source",
        QCoreApplication::translate("main", "Source file to read [FilePath...\\NameSource.(toml | toml)].")));
}
QString GetDescription()
{
    QString description;
    description += "\nConsole application that accepts a configuration file as a parameter.\n";
    description += "The file from which the application should read the parameter list\n";
    description += "must be in .toml , .toml format<br> (Filename extension - .toml , .toml)";
    return description;
}
