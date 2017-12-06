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
int Trace::length()
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
    return datas()[base];
}
//-----------------------------------------------------------------
QStringList Trace::keys() const
{
    return mMetadatas.keys();
}
//-----------------------------------------------------------------
const QVariant& Trace::value(const QString &key)
{
    return mMetadatas[key];
}
//-----------------------------------------------------------------
bool Trace::isValid() const
{
    // need to improve

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
    QVector<int> new_baseLocations       = baseLocations();
    QVector<int> new_baseScores          = baseScores();
    Sequence new_sequence                = sequence().reverse();

    // reverse datas orientation
    QHashIterator<QChar, QVector<int>>i(datas());
    while (i.hasNext()) {
        i.next();
        QVector<int> values = i.value();
        std::reverse(values.begin(), values.end());
        new_datas[NucleotidAlphabet::complement(i.key())] = values;
    }




    return Trace(new_datas, new_baseLocations, new_baseScores, new_sequence);


}

