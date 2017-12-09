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

void Trace::cut(int start, int len)
{

    if (!isValid())
        return;

    // be carefull with the range
    if ( start < 0)
        start = 0;

    if (start+len > mBaseLocations.length())
        len = mBaseLocations.length() - 1 - start;

    // get trace coordinate of the range
    int tstart  = mBaseLocations.at(start);
    int tend    = mBaseLocations.at(start+len);



    // remove trace in the range
    QHashIterator <QChar, QVector<int>>i(mDatas);
    while (i.hasNext())
    {
        i.next();
        QVector<int> &v = mDatas[i.key()];
        // erase / remove_if pattern . Thanks to std oneliner
        v.erase(v.begin()+tstart, v.begin()+tstart+tend);

    }

    //remove other region in containers
    mBaseLocations.erase(mBaseLocations.begin() + start , mBaseLocations.begin()+start + len);
    mBaseScores.erase(mBaseScores.begin() + start , mBaseScores.begin()+start + len);
    mSequence.cut(start, len);

}

void Trace::trimLeft(int size)
{

    cut(0, size);

}
void Trace::trimRight(int size)
{

    cut(mBaseLocations.length()-size, mBaseLocations.length());
}

