#ifndef ABSTRACTTRACEWRITER_H
#define ABSTRACTTRACEWRITER_H
#include <QtCore>
#include "trace.h"

class Trace;
class AbstractTraceWriter
{
public:
    explicit AbstractTraceWriter(QIODevice * device);

    /*!
     * \brief traces
     * \return trace vector for each nucleotids
     */
    virtual void writeDatas(const QHash<QChar, QVector<int>>& datas) = 0;
    /*!
     * \brief baseCalls
     * \return Sequence.
     * \todo should be a Sequence
     */
    virtual void writeSequence(const Sequence& sequence)  = 0 ;
    /*!
     * \brief baseLocations
     * \return base location in trace coordinate
     */
    virtual void writeBaseLocations(const QVector<int>& locations)  = 0;
    /*!
     * \brief confScores
     * \return confident score for each basecalls
     */
    virtual void writeBaseScores(const QVector<int>& scores )  = 0;
    /*!
     * \brief metadatas
     * can be empty
     * \return metadata
     */
    virtual void writeMetadatas(const QHash<QString, QVariant>& meta) = 0;


    /*!
     * \brief createTrace
     * construct the trace using virtual methods
     * \return Trace object
     */
     virtual void writeTrace(Trace * trace) = 0;


    QIODevice *device();

private:
    QIODevice * mDevice;
};

#endif // ABSTRACTTRACEWRITER_H
