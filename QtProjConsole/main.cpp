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

        return app.exec();
        

    }
    catch (const MyException& message)
    {
        qCritical() << "Error : " << message.Get();
    }
    catch (const QUnhandledException& message)
    {
        qCritical() << "Uncaught error ";
    }
    catch(...)
    {
        qCritical() << "Uncaught error qexception!";
    }


}

void CheckCommandLineArguments(const QCommandLineParser& parser, QString& optionSet, const QString& defPath)
{
    QVector<bool> indexArray;
    QTextStream out(stdout);
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
            optionSet += "\\source";
        }
    }
    for (auto val : optionSet)
        out << val;
    out << Qt::endl;
}

void GetCommandLine(const QCoreApplication& app, QCommandLineParser& parser)
{
    QCoreApplication::setApplicationName("Read .tolow");

    parser.setApplicationDescription(GetDescription());
    parser.addHelpOption();

    SetOptionsSingle(parser);
    SetOptionsMultiple(parser);

    parser.addPositionalArgument("-s, --source", QCoreApplication::translate("main",
        "Source file to read \"source.toml\" | \"source.toml11\"."), "[-p] [-d] | ([-s] | [--source]) <source> ");

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
        QCoreApplication::translate("main", "Default source file to read \"source.toml\" | \"source.toml11\"")));
    parser.addOption(QCommandLineOption(QStringList() << "s" << "source",
        QCoreApplication::translate("main", "Source file to read [FilePath...\\NameSource.(toml | toml11)].")));
}
QString GetDescription()
{
    QString description;
    description += "\nConsole application that accepts a configuration file as a parameter.\n";
    description += "The file from which the application should read the parameter list\n";
    description += "must be in .toml , .toml11 format<br> (Filename extension - .toml , .toml11)";
    return description;
}
