#include "main.h"


int main(int argc, char **argv)
{

    QCoreApplication app(argc, argv);
    QTextStream out(stdout);
    QCommandLineParser parser;   
    QString optionSet;
    GetCommandLine(app, parser);
  
    return app.exec();
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