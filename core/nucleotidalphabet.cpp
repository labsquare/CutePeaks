#include "nucleotidalphabet.h"

NucleotidAlphabet *NucleotidAlphabet::mInstance = nullptr;

NucleotidAlphabet::NucleotidAlphabet()
{
    initNames();
    initComplements();
}

QString NucleotidAlphabet::name(unsigned char iupac)
{
    if ( i()->mNames.contains(iupac))
        return i()->mNames.value(iupac,QString());

    return QString();
}

unsigned char NucleotidAlphabet::complement(unsigned char iupac)
{
    return i()->mTables.at(iupac);
}

bool NucleotidAlphabet::isGorC(char nuc)
{
    return nuc == 'G' || nuc == 'C' || nuc == 'c' || nuc == 'g';
}

bool NucleotidAlphabet::isGorC(QChar nuc)
{
    return NucleotidAlphabet::isGorC(nuc.row());
}

NucleotidAlphabet *NucleotidAlphabet::i()
{
    // use QMutex to protected thread
    if (!NucleotidAlphabet::mInstance){
        NucleotidAlphabet::mInstance = new NucleotidAlphabet;
    }

    return NucleotidAlphabet::mInstance;

}
void NucleotidAlphabet::initNames()
{
    mNames = {
        {'-',"gap"},
        {'.',"gap"},
        {'A',"Adenine"},
        {'B',"C or G or T"},
        {'C',"Cytosine"},
        {'D',"A or G or T"},
        {'G',"Guanine"},
        {'H',"A or C or T"},
        {'K',"G or T"},
        {'M',"A or C"},
        {'N',"any base"},
        {'R',"A or G"},
        {'S',"G or C"},
        {'T',"Thymine"},
        {'U',"Uracil"},
        {'V',"A or C or G"},
        {'W',"A or T"},
        {'Y',"C or G"}
    };
}

void NucleotidAlphabet::initComplements()
{
    mTables = QVector<unsigned char> (122);
    mTables.fill('?');

    mTables['-'] = '-'; // gap
    mTables['.'] = '.'; // gap
    mTables['A'] = 'T'; // Adenine
    mTables['B'] = 'B'; // C or G or T
    mTables['C'] = 'G'; // Cytosine
    mTables['D'] = 'D'; // A or G or T
    mTables['G'] = 'C'; // Guanine
    mTables['H'] = 'H'; // A or C or T
    mTables['K'] = 'K'; // G or T
    mTables['M'] = 'M'; // A or C
    mTables['N'] = 'N'; // any base
    mTables['R'] = 'R'; // A or G
    mTables['S'] = 'S'; // G or C
    mTables['T'] = 'A'; // Thymine
    mTables['U'] = 'A'; // Uracil
    mTables['V'] = 'V'; // A or C or G
    mTables['W'] = 'W'; // A or T
    mTables['Y'] = 'Y'; // C or G
    mTables['a'] = 't'; // Adenine
    mTables['b'] = 'b'; // C or G or T
    mTables['c'] = 'g'; // Cytosine
    mTables['d'] = 'd'; // A or G or T
    mTables['g'] = 'c'; // Guanine
    mTables['h'] = 'h'; // A or C or T
    mTables['k'] = 'k'; // G or T
    mTables['m'] = 'm'; // A or C
    mTables['n'] = 'n'; // any base
    mTables['r'] = 'r'; // A or G
    mTables['s'] = 's'; // G or C
    mTables['t'] = 'a'; // Thymine
    mTables['u'] = 'a'; // Uracil
    mTables['v'] = 'v'; // A or C or G
    mTables['w'] = 'w'; // A or T
    mTables['y'] = 'y'; // C or G
}
