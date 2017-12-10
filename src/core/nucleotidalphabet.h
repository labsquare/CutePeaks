#ifndef NUCLEOTIDALPHABET_H
#define NUCLEOTIDALPHABET_H
#include <QHash>
#include <QVector>
#include <QChar>

class NucleotidAlphabet
{
private:
    NucleotidAlphabet();

public:

    static QString name(unsigned char iupac);
    static unsigned char complement(unsigned char iupac);
    static QChar complement(const QChar& iupac);


    static NucleotidAlphabet * i();

    static bool isGorC(char nuc);
    static bool isGorC(QChar nuc);

private:

    void initNames();
    void initComplements();

    QHash<unsigned char, QString> mNames;
     QVector<unsigned char> mTables;
    static NucleotidAlphabet *mInstance;


};


#endif // NUCLEOTIDALPHABET_H
