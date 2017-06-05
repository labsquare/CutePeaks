#ifndef ABSTRACTSEQUENCETRACE_H
#define ABSTRACTSEQUENCETRACE_H
#include <QtCore>

class AbstractSequenceTrace
{
public:
    explicit AbstractSequenceTrace(QIODevice * device);
    const QVector<int>& traces(const QChar& base) const;
    const QByteArray& baseCalls()const;
    const QVector<int>& baseLocations()const;
    const QVector<int>& confScores()const;


protected:
    virtual bool loadData() = 0;
    void setTrace(const QChar& base , const QVector<int>& data);
    void setBaseCalls(const QByteArray& data);
    void setBaseLocations(const QVector<int>& locations);
    void setConfScores(const QVector<int>& scores);
    QIODevice * device();


private:
    QHash<QChar, QVector<int>> mTraces;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    QByteArray mBaseCalls;
    QIODevice * mDevice;

};

#endif // ABSTRACTSEQUENCETRACE_H
