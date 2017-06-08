#include "sequence.h"

Sequence::Sequence(const char *data)
    :mArray(data), mStrand(Forward),mType(Dna)
{

}

Sequence::Sequence(const QByteArray &bytes)
    :mArray(bytes), mStrand(Forward),mType(Dna)
{

}

Sequence::Sequence()
    :mArray(), mStrand(Forward),mType(Dna)
{

}

Sequence::Sequence(const QByteArray &bytes, Sequence::Strand strand, Sequence::Type type)
    :mArray(bytes), mStrand(strand), mType(type)
{

}

Sequence Sequence::complement() const
{
    if (type() == Protein)
    {
        qWarning()<<"cannot complement a protein";
        return Sequence();
    }

    QByteArray c;
    c.fill('A', length());

    auto src_begin = byteArray().begin();
    auto src_end = byteArray().end();
    auto c_begin = c.begin();
    for(; src_begin <= src_end; src_begin++, c_begin++)
    {
        *c_begin = NucleotidAlphabet::complement(*src_begin);
    }

    Sequence newSeq(c);
    newSeq.setName(name());
    newSeq.setStrand(strand());
    newSeq.setType(type());

    return newSeq;

}
Sequence Sequence::translate(ReadFame frame) const
{
    // TODO
    if (type() == Protein)
    {
        qWarning()<<"cannot translate a protein";
        return Sequence();
    }

    // SACHA NAIVE CODE
    int start = 0;
    switch (frame)
    {
    case Frame1: start = 0; break;
    case Frame2: start = 1; break;
    case Frame3: start = 2; break;
    default : start = 0;
    }

    Sequence protein;
    protein.setType(Protein);
    protein.setName(name());

    for (int i= start; i<=byteArray().length()-3; i+=3)
    {
        protein.append(ProteinAlphabet::codonToAA(byteArray().mid(i,3)));

    }

    return protein;
}

Sequence Sequence::reverse() const
{
    QByteArray c;
    c.fill('A', length());

    auto src_begin = this->byteArray().begin();
    auto src_end = this->byteArray().end(); src_end--;
    auto c_begin = c.begin();
    auto c_end = c.end(); c_end--;
    for(; src_begin <= src_end; src_begin++, src_end--, c_begin++, c_end--)
    {
        *c_begin = *src_end;
        *c_end = *src_begin;
    }

    Sequence newSeq = Sequence(c);
    newSeq.setStrand(strand() == Forward ? Reverse : Forward);
    newSeq.setType(type());
    newSeq.setName(name());
    return newSeq;
}

QString Sequence::name() const
{
    return mName;
}

void Sequence::setName(const QString &name)
{
    mName = name;
}

Sequence::Strand Sequence::strand() const
{
    return mStrand;
}

void Sequence::setStrand(const Sequence::Strand &strand)
{
    mStrand = strand;
}

Sequence::Type Sequence::type() const
{
    return mType;
}

void Sequence::setType(const Sequence::Type &type)
{
    mType = type;
}

QString Sequence::typeName()
{
    switch ( type())
    {
    case Dna: return "dna";
    case Rna: return "rna";
    case Protein:return "protein";
    default : return "unknown";
    }
}

int Sequence::length() const
{
    return mArray.length();
}

char Sequence::at(int index) const
{
    return mArray.at(index);
}


void Sequence::setByteArray(const QByteArray &array)
{
    mArray = array;
}

const QByteArray &Sequence::byteArray() const
{
    return mArray;
}

QString Sequence::toString(Format format) const
{
    if (type() == Protein)
    {
        if (format == SymbolFormat)
            return QString::fromUtf8(byteArray());

        if (format == HumanFormat)
        {
            QString out;
            for (char c : byteArray())
                out.append(ProteinAlphabet::shortName(c));
            return out;
        }

        if (format == ShortFormat)
        {
            QString out;
            for (char c : byteArray())
                out.append(ProteinAlphabet::name(c));
            return out;
        }

    }

    if (type() == Dna || type() == Rna)
    {
        if (format == SymbolFormat)
            return QString::fromUtf8(byteArray());

        else {
            QString out;
            for (char c : byteArray())
                out.append(NucleotidAlphabet::name(c));
            return out;
        }
    }


    return QString::fromUtf8(byteArray());

}

float Sequence::gcPercent() const
{
    float gc = 0;
    for(auto it = this->mArray.begin(); it != this->mArray.end(); it++)
    {
        if(NucleotidAlphabet::isGorC(*it))
            gc++;
    }

    return gc/this->mArray.length();
}

void Sequence::append(char base)
{
    mArray.append(base);
}
