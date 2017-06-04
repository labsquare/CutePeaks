#ifndef ABSTRACTSEQUENCETRACE_H
#define ABSTRACTSEQUENCETRACE_H
#include <QtCore>

class AbstractSequenceTrace
{
public:
   explicit AbstractSequenceTrace(QIODevice * device);
   explicit AbstractSequenceTrace(const QString& filename);

    const QVector<int>& traces(const QChar& base);


private:
    QHash<QChar, QVector<int>> mTraces;
    QIODevice * mDevice;

};

#endif // ABSTRACTSEQUENCETRACE_H
