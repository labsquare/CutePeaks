#include "commandlineinterpreter.h"

CommandLineInterpreter::CommandLineInterpreter(QApplication *app)
    :mApp(app)
{
    mParser.setApplicationDescription(mApp->applicationName());
    mParser.addHelpOption();
    mParser.addVersionOption();
    mParser.addPositionalArgument("file", "ab1 or scf file");
    mParser.addOption({"fasta", "export sequence"});
    mParser.addOption({"tsv", "export trace data as tabular"});
    mParser.addOption({"metadatas", "print metadatas"});
    mParser.process(*app);

}

bool CommandLineInterpreter::needCLI() const
{

    for (QString option : mParser.optionNames())
        if (mParser.isSet(option))
            return true;

    return false;

}

bool CommandLineInterpreter::process()
{
    if (mParser.positionalArguments().isEmpty())
    {
        std::cerr<<"filename not provided"<<std::endl;
        return false;
    }

    QString filename = mParser.positionalArguments().first();

    if (!QFile::exists(filename))
    {
        std::cerr<<"filename doesn't exist"<<std::endl;
        return false;
    }

    if (mParser.isSet("metadatas"))
        return printMetadatas();

    if (mParser.isSet("fasta"))
        return printFasta();

    if (mParser.isSet("tsv"))
        return printTsv();

    return false;
}

bool CommandLineInterpreter::printMetadatas()
{

    QScopedPointer<Trace>trace(TraceFactory::createTrace(filename()));

    if (!trace->isValid())
    {
        std::cerr<<"this trace file is not supported"<<std::endl;
        return false;
    }

    std::cout<<std::setw(10)<<"base count " << trace->baseCount()<<std::endl;

    auto it  = trace->metadatas().begin();
    while (it != trace->metadatas().end())
    {

        QString val = it.value().toString();

        std::cout<<std::setw(10)<<std::left<<it.key().toStdString()<<val.toStdString()<<std::endl;

        ++it;
    }

    return true;
}

bool CommandLineInterpreter::printTsv()
{
    QScopedPointer<Trace>trace(TraceFactory::createTrace(filename()));
    for (int i=0; i< trace->datas().begin()->size(); ++i)
    {
        QStringList row;
        if (i==0)
        {
            for (QChar key : trace->datas().keys())
                row.append(key);
            std::cout<<"#"<<row.join('\t').toStdString()<<std::endl;
            row.clear();
        }

        for (QChar key : trace->datas().keys())
            row.append(QString::number(trace->datas()[key][i]));

        std::cout<<row.join('\t').toStdString()<<std::endl;
    }
    return true;
}

bool CommandLineInterpreter::printFasta()
{
    QScopedPointer<Trace>trace(TraceFactory::createTrace(filename()));
    std::cout<<trace->sequence().toFasta("sequence").toStdString()<<std::endl;
    return true;
}

QString CommandLineInterpreter::filename() const
{
    if (mParser.positionalArguments().isEmpty())
        return QString();

    return mParser.positionalArguments().first();
}

