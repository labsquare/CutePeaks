#ifndef PROTEINALPHABET_H
#define PROTEINALPHABET_H
#include <QtCore>
class ProteinAlphabet
{
private:
    ProteinAlphabet();



public:
    void initGeneticCode();
    void initNames();

    static QString name(unsigned char iupac);
    static QString shortName(unsigned char iupac);
    static unsigned char codonToAA(const QByteArray& codon);


    static ProteinAlphabet* i();


private:
    static ProteinAlphabet *mInstance;
    // codon to AA
    QHash<unsigned char, QPair<QString,QString> > mNames;
    QHash<QByteArray, unsigned char> mCodes;



};


#endif // PROTEINALPHABET_H
