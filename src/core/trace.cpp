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

    if (mDatas.isEmpty())
        return false;

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
void Trace::revert()
{
    if (!isValid())
        return ;

    // complements ...
    mDatas['A'].swap(mDatas['T']);
    mDatas['C'].swap(mDatas['G']);

    // reverse
    for (auto &it : mDatas)
        std::reverse(it.begin(), it.end());

    int size = mDatas['A'].size();
    std::reverse(mBaseLocations.begin(), mBaseLocations.end());
    std::for_each(mBaseLocations.begin(),
                  mBaseLocations.end(),
                  [&size](int &x){x = size-x;});


    computeShiftBaseLocations();
    mSequence.revert();

}
//-----------------------------------------------------------------
Trace * Trace::cut(int start, int len)
{
    if (!isValid())
        return nullptr;

    // be carefull with the range
    if ( start < 0)
        start = 0;

    // Create new Trace containers
    QHash<QChar, QVector<int>> newData;
    QVector<int> newBaseLocations;
    QVector<int> newBaseScores;
    Sequence newSequence;

    // extract trace coord to remove
    int traceStart = shiftBaseLocations()[start];
    int traceEnd   = shiftBaseLocations()[start+len];

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

    // copy new base location
    std::copy(mBaseLocations.begin() + start , mBaseLocations.begin()+start + len, std::back_inserter(newBaseLocations));

    //    // Shift base location on new
    for (auto& val : newBaseLocations)
        val = val - (traceStart);

    // erase base location on original
    auto last = mBaseLocations.erase(mBaseLocations.begin() + start , mBaseLocations.begin()+ start + len);

    //    // Shift base location on original
    for (auto it = last ; it!= mBaseLocations.end(); ++it)
        (*it) = (*it) - (traceEnd - traceStart);

    // compute new shift
    computeShiftBaseLocations();

    // copy baseScore and remove
    std::copy(mBaseScores.begin() + start , mBaseScores.begin()+start + len, std::back_inserter(newBaseScores));
    mBaseScores.erase(mBaseScores.begin() + start , mBaseScores.begin()+start + len);

    //remove other region in containers
    newSequence = mSequence.mid(start,len);
    mSequence.remove(start, len);

    Trace * newTrace = new Trace(newData,newBaseLocations,newBaseScores,newSequence, metadatas());
    newTrace->setInsertPos(traceStart);
    newTrace->setInsertIndex(start);

    return newTrace;

}
//-----------------------------------------------------------------
void Trace::paste(Trace *trace)
{

    // get insert position
    int traceStart = trace->insertPos();
    int start      = trace->insertIndex();
    int insertSize = trace->mDatas.begin()->size();

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

    for (auto it = mBaseLocations.begin()+start; it != mBaseLocations.end(); ++it)
        (*it) = (*it)+insertSize;


    std::copy(insertBaseLocation.begin(),
              insertBaseLocation.end(),
              std::inserter(mBaseLocations, mBaseLocations.begin()+start));


    computeShiftBaseLocations();

    std::copy(trace->baseScores().begin(), trace->baseScores().end(),
              std::inserter(mBaseScores, mBaseScores.begin()+start));

    mSequence.insert(start, trace->sequence());

}

void Trace::trimLeft(int size)
{

    cut(0, size);

}
void Trace::trimRight(int size)
{

    cut(mBaseLocations.length()-size, mBaseLocations.length());
}

void Trace::debug() const
{

    qDebug()<<"Trace Size: "<<mDatas['A'].size();
    qDebug()<<"Sequence Size: "<<sequence().length();
    qDebug()<<"Sequence: "<<sequence().byteArray();





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
    mShiftBaseLocation.append(mDatas.begin()->size()-1);
}

int Trace::insertIndex() const
{
    return mInsertIndex;
}

void Trace::setInsertIndex(int insertIndex)
{
    mInsertIndex = insertIndex;
}

void Trace::setInsertPos(int insertPos)
{
    mInsertPos = insertPos;
}

int Trace::insertPos() const
{
    return mInsertPos;
}

