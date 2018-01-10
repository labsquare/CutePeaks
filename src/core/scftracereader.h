#ifndef SCFSEQUENCETRACE_H
#define SCFSEQUENCETRACE_H
#include "abstracttracereader.h"
#include <limits>
#include "scfheader.h"

class ScfTraceReader : public AbstractTraceReader
{
public:
    ScfTraceReader(QIODevice * device);

    const QHash<QChar, QVector<int>>& readDatas() const override;
    const Sequence& readSequence()const  override;
    const QVector<int>& readBaseLocations()const  override;
    const QVector<int>& readBaseScores()const  override;
    const QHash<QString, QVariant>& readMetadatas() const override;

    QByteArray version() const;

protected:
    bool load();

    void readHeader();
    void readMetadatas();
    void readBases();
    template <typename T>
    void readTraces();
    template<typename T>
    void decodeDelta(QVector<T>& data);



private:
    ScfHeader mHeader;
    // store data
    QHash<QChar, QVector<int>> mTraces;
    QHash<QString, QVariant> mMetadatas;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    Sequence mBaseCalls;
//    QIODevice * mDevice;

    QHash<QChar, QList<quint8>> mTempProba;

};

#endif // SCFSEQUENCETRACE_H
