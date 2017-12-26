#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <QCommandLineParser>
#include <QApplication>
#include <iostream>
#include <iomanip>      // std::setw

#include "traceview.h"

class CommandLineInterpreter
{
public:
    CommandLineInterpreter(QApplication * app);
    bool needCLI() const;
    bool process();
    QString filename() const;


protected:
    bool printMetadatas();
    bool printFasta();
    bool printTsv();

private:
    QCommandLineParser mParser;
    QApplication * mApp;
    QStringList mTypeAvaible = {"fasta","tsv"};
};

#endif // COMMANDLINE_H
