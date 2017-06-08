#include "proteinalphabet.h"

ProteinAlphabet * ProteinAlphabet::mInstance = nullptr;

ProteinAlphabet::ProteinAlphabet()
{
    initNames();
    initGeneticCode();
}

void ProteinAlphabet::initGeneticCode()
{
    mCodes = {
        {"TTT" , 'F'},
        {"TTC" , 'F'},
        {"TTA" , 'L'},
        {"TTG" , 'L'},
        {"CTT" , 'L'},
        {"CTC" , 'L'},
        {"CTA" , 'L'},
        {"CTG" , 'L'},
        {"ATT" , 'I'},
        {"ATC" , 'I'},
        {"ATA" , 'I'},
        {"ATG" , 'M'},
        {"GTT" , 'V'},
        {"GTC" , 'V'},
        {"GTA" , 'V'},
        {"GTG" , 'V'},
        {"TCT" , 'S'},
        {"TCC" , 'S'},
        {"TCA" , 'S'},
        {"TCG" , 'S'},
        {"CCT" , 'P'},
        {"CCC" , 'P'},
        {"CCA" , 'P'},
        {"CCG" , 'P'},
        {"ACT" , 'T'},
        {"ACC" , 'T'},
        {"ACA" , 'T'},
        {"ACG" , 'T'},
        {"GCT" , 'A'},
        {"GCC" , 'A'},
        {"GCA" , 'A'},
        {"GCG" , 'A'},
        {"TAT" , 'F'},
        {"TAC" , 'F'},
        {"TAA" , '.'},
        {"TAG" , '.'},
        {"CAT" , 'H'},
        {"CAC" , 'H'},
        {"CAA" , 'Q'},
        {"CAG" , 'Q'},
        {"AAT" , 'N'},
        {"AAC" , 'N'},
        {"AAA" , 'K'},
        {"AAG" , 'K'},
        {"GAT" , 'D'},
        {"GAC" , 'D'},
        {"GAA" , 'E'},
        {"GAG" , 'E'},
        {"TGT" , 'C'},
        {"TGC" , 'C'},
        {"TGA" , '.'},
        {"TGG" , 'W'},
        {"CGT" , 'R'},
        {"CGC" , 'R'},
        {"CGA" , 'R'},
        {"CGG" , 'R'},
        {"AGT" , 'S'},
        {"AGC" , 'S'},
        {"AGA" , 'R'},
        {"AGG" , 'R'},
        {"GGT" , 'G'},
        {"GGC" , 'G'},
        {"GGA" , 'G'},
        {"GGG" , 'G'},


    };


}

void ProteinAlphabet::initNames()
{
    mNames = {
        {'A',{"Ala", "Alanine"}},
        {'C',{"Cys", "Cysteine"}},
        {'D',{"Asp", "Aspartic Acid"}},
        {'E',{"Glu", "Glutamic Acid"}},
        {'F',{"Phe", "Phenylalanine"}},
        {'G',{"Gly", "Glycine"}},
        {'H',{"His", "Histidine"}},
        {'I',{"Ile", "Isoleucine"}},
        {'K',{"Lys", "Lysine"}},
        {'L',{"Leu", "Leucine"}},
        {'M',{"Met", "Methionine"}},
        {'N',{"Asn", "Asparagine"}},
        {'P',{"Pro", "Proline"}},
        {'Q',{"Gln", "Glutamine"}},
        {'R',{"Arg", "Arginine"}},
        {'S',{"Ser", "Serine"}},
        {'T',{"Thr", "Threonine"}},
        {'V',{"Val", "Valine"}},
        {'W',{"Trp", "Tryptophan"}},
        {'Y',{"Tyr", "Tyrosine"}},
        {'Y',{"Tyr", "Tyrosine"}},
        {'.',{"Stop", "Stop"}}
    };
}

QString ProteinAlphabet::name(unsigned char iupac)
{
    if (i()->mNames.contains(iupac))
    {
        return i()->mNames[iupac].first;
    }

    return QString();
}

QString ProteinAlphabet::shortName(unsigned char iupac)
{
    if (i()->mNames.contains(iupac))
    {
        return i()->mNames[iupac].second;
    }

    return QString();
}

unsigned char ProteinAlphabet::codonToAA(const QByteArray &codon)
{
    if (i()->mCodes.contains(codon))
        return i()->mCodes[codon];

    return '?';
}

ProteinAlphabet *ProteinAlphabet::i()
{
    // use QMutex to protected thread
    if (!ProteinAlphabet::mInstance){
        ProteinAlphabet::mInstance = new ProteinAlphabet;
    }

    return mInstance;
}
