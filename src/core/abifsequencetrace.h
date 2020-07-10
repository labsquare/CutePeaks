#ifndef ABIFSEQUENCETRACE_H
#define ABIFSEQUENCETRACE_H

#include "abstracttracereader.h"
#include "tracy/abif.h"


class AbifSequenceTrace : public AbstractTraceReader
{
public:
    AbifSequenceTrace(QIODevice * device);

    const QHash<QChar, QVector<int>>& datas() const override;
    const Sequence& sequence()const  override;
    const QVector<int>& baseLocations()const  override;
    const QVector<int>& baseScores()const  override;
    const QHash<QString, QVariant>& metadatas() const override;

protected:
    void readData();

private:
    tracy::Trace mTrace;
    qint16 mVersion;
    // store data
    QHash<QChar, QVector<int>> mTraces;
    QHash<QString, QVariant> mMetadatas;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    Sequence mBaseCalls;

//    QIODevice * mDevice;


};



#endif // ABIFSEQUENCETRACE_H
