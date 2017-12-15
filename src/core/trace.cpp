#include "trace.h"
#include <algorithm>
#include "nucleotidalphabet.h"

Trace::Trace(const QHash<QChar, QVector<int> > datas,
             const QVector<int> &baseLocations,
             const QVector<int> &baseScores,
             const Sequence &sequence,
             const QHash<QString, QVariant>& metadatas)
    :mDatas(datas),mBaseLocations(baseLocations), mBaseScores(baseScores),mSequence(sequence),mMetadatas(metadatas)
{

    // compute shift base location
    computeShiftBaseLocations();


}
//-----------------------------------------------------------------
const QHash<QChar, QVector<int> > &Trace::datas() const
{
    return mDatas;
}
//-----------------------------------------------------------------
const QVector<int> &Trace::baseLocations() const
{
    return mBaseLocations;
}

int Trace::baseCount() const
{
    return mSequence.length();
}
//-----------------------------------------------------------------
const QVector<int> &Trace::shiftBaseLocations() const
{
    return mShiftBaseLocation;
}
//-----------------------------------------------------------------
const QVector<int> &Trace::baseScores() const
{
    return mBaseScores;
}
//-----------------------------------------------------------------
const Sequence &Trace::sequence() const
{
    return mSequence;
}
//-----------------------------------------------------------------
int Trace::length() const
{
    if (datas().isEmpty())
        return 0;

    QChar key = datas().keys().first();
    return datas()[key].count();
}
//-----------------------------------------------------------------
QList<QChar> Trace::basesAvaible() const
{
    return datas().keys();

}
//-----------------------------------------------------------------
QVector<int> Trace::data(const QChar &base) const
{
    return datas().value(base);
}
//-----------------------------------------------------------------
const QHash<QString, QVariant> &Trace::metadatas()
{
    return mMetadatas;
}
//-----------------------------------------------------------------
QStringList Trace::keys() const
{
    return mMetadatas.keys();
}
//-----------------------------------------------------------------
QVariant Trace::value(const QString &key) const
{
    return mMetadatas.value(key);
}

//-----------------------------------------------------------------
bool Trace::isValid() const
{


    // need to improve
    if (!datas().contains('A'))
        return false;

    if (data('A').isEmpty())
        return false;

    if (baseLocations().length() == 0)
        return false;

    if (baseLocations().length() != sequence().length())
        return false;

    return true;
}
//-----------------------------------------------------------------
Trace Trace::reverse() const
{
    QHash<QChar, QVector<int>> new_datas;
    QVector<int> new_baseLocations;
    QVector<int> new_baseScores;
    Sequence new_sequence;

    // reverse datas orientation
    QHashIterator<QChar, QVector<int>>i(datas());
    while (i.hasNext()) {
        i.next();
        QVector<int> values = i.value();
        std::reverse(values.begin(), values.end());
        new_datas[NucleotidAlphabet::complement(i.key())] = values;
    }

    // reverse base location
    new_baseLocations = baseLocations();
    std::reverse(new_baseLocations.begin(), new_baseLocations.end());

    // reverse base score
    new_baseScores = baseScores();
    std::reverse(new_baseScores.begin(), new_baseScores.end());

    // reverse sequence
    new_sequence = sequence().reverse();

    return Trace(new_datas, new_baseLocations, new_baseScores, new_sequence, mMetadatas);


}
//-----------------------------------------------------------------
Trace * Trace::take(int start, int len)
// peaks     = ACGTATATATAT
// interpeak = les coordonnées entre deux pic

// trace = 1,2,3,4,12,10,8,1,2,3,43,2,11,
// peaks[2] = 11 index dans trace
// TODO : rename trace to amplitude
{
    if (!isValid())
        return nullptr;

    // be carefull with the range
    if ( start < 0)
        start = 0;

    if (start+len > mBaseLocations.length())
        len = mBaseLocations.length() - 1 - start;

    // Create new Trace containers
    QHash<QChar, QVector<int>> newData;
    QVector<int> newBaseLocations;
    QVector<int> newBaseScores;
    Sequence newSequence;

    // extract trace coord to remove
    int traceStart = shiftBaseLocations()[start];
    int traceEnd   = shiftBaseLocations()[start+len];

    int ttStart = baseLocations()[start];
    int ttEnd   = baseLocations()[start+len];

    qDebug()<<"start / len"<<start<<" "<<len;

    // Loop over all data trace, take part from original and put into the new trace. Then remove from original
    QHashIterator <QChar, QVector<int>>i(mDatas);
    while (i.hasNext())
    {
        i.next();

        QVector<int> &v = mDatas[i.key()];
        QVector<int> c;

        // copy area to c
        std::copy(v.begin()+traceStart, v.begin()+traceEnd, std::back_inserter(c));
        // todo move !
        // remove area from v
        v.erase(v.begin()+traceStart, v.begin()+traceEnd);

        // insert vector into newData
        newData[i.key()] = c;
    }

    //    //    // copy new base location
    std::copy(mBaseLocations.begin() + start , mBaseLocations.begin()+start + len, std::back_inserter(newBaseLocations));

    //    // Shift base location on new
    for (auto& val : newBaseLocations)
        val = val - (traceStart);

    // erase base location on original
    auto last = mBaseLocations.erase(mBaseLocations.begin() + start , mBaseLocations.begin()+start + len);

    //    // Shift base location on original
    for (auto it = last ; it!= mBaseLocations.end(); ++it)
        (*it) = (*it) - (traceEnd - traceStart);

   int delta =(traceEnd - traceStart);


    computeShiftBaseLocations();

    //    // copy baseScore and remove
    std::copy(mBaseScores.begin() + start , mBaseScores.begin()+start + len, std::back_inserter(newBaseScores));
    mBaseScores.erase(mBaseScores.begin() + start , mBaseScores.begin()+start + len);

    //    //remove other region in containers
    newSequence = mSequence.mid(start,len);
    mSequence.remove(start, len);

    return new Trace(newData,newBaseLocations,newBaseScores,newSequence, metadatas());

}
//-----------------------------------------------------------------
void Trace::insert(int pos, Trace *trace)
{

    // extract trace coord to remove
    int traceStart = shiftBaseLocations()[pos];
    int b = shiftBaseLocations()[pos+1];


    // Insert trace section
    QHashIterator <QChar, QVector<int>>i(mDatas);
    while (i.hasNext())
    {
        i.next();

        QVector<int> &source      = mDatas[i.key()];
        const QVector<int> insert = trace->datas()[i.key()];

        std::copy(insert.begin(), insert.end(), std::inserter(source, source.begin()+traceStart));

    }


    QVector<int> insertBaseLocation = trace->baseLocations();

    //    // shift insert
        for (int &i : insertBaseLocation)
            i += traceStart;



   int ts = trace->shiftBaseLocations().first();
   int te = 3;

   int delta = trace->shiftBaseLocations().last()+ (mShiftBaseLocation.at(pos+1) - mShiftBaseLocation.at(pos));

    qDebug()<<"delta" <<delta;


    // shift right
   // find 192 !!!!
    for (auto it = mBaseLocations.begin()+pos; it != mBaseLocations.end(); ++it)
        (*it) = (*it) + delta;


    std::copy(insertBaseLocation.begin(),
              insertBaseLocation.end(),
              std::inserter(mBaseLocations, mBaseLocations.begin()+pos));


    computeShiftBaseLocations();


    std::copy(trace->baseScores().begin(), trace->baseScores().end(),
              std::inserter(mBaseScores, mBaseScores.begin()+pos));

    mSequence.insert(pos, trace->sequence());



}

void Trace::trimLeft(int size)
{

    take(0, size);

}
void Trace::trimRight(int size)
{

    take(mBaseLocations.length()-size, mBaseLocations.length());
}

void Trace::debug() const
{

    qDebug()<<"trace size :"<<mDatas['A'].size();
    qDebug()<<"seq size"<<sequence().length();
    qDebug()<<"seq: "<<sequence().byteArray();





}

void Trace::computeShiftBaseLocations()
{
    if (mBaseLocations.isEmpty())
        return;

    mShiftBaseLocation.clear();
    std::adjacent_difference(mBaseLocations.begin(),
                             mBaseLocations.end(),
                             std::back_inserter(mShiftBaseLocation),
                             [](int a,int b){return b+std::ceil((a-b)/2);});

    mShiftBaseLocation[0] = 0;
}

