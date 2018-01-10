#ifndef ABSTRACTTRACEWRITER_H
#define ABSTRACTTRACEWRITER_H
#include <QtCore>
#include "trace.h"

class Trace;
class AbstractTraceWriter;
class AbstractTraceWriter
{
public:
    AbstractTraceWriter(QIODevice * device);
    virtual ~AbstractTraceWriter();

    /*!
     * \brief traces
     * \return trace vector for each nucleotids
     */
    virtual void writeDatas(const QHash<QChar, QVector<int>>& datas) const = 0;
    /*!
     * \brief baseCalls
     * \return Sequence.
     * \todo should be a Sequence
     */
    virtual void writeSequence(const Sequence& sequence) const  = 0 ;
    /*!
     * \brief baseLocations
     * \return base location in trace coordinate
     */
    virtual void writeBaseLocations(const QVector<int>& locations)const  = 0;
    /*!
     * \brief confScores
     * \return confident score for each basecalls
     */
    virtual void writeBaseScores(const QVector<int>& scores )const  = 0;
    /*!
     * \brief metadatas
     * can be empty
     * \return metadata
     */
    virtual void writeMetadatas(const QHash<QString, QVariant>& ) const = 0;


    /*!
     * \brief createTrace
     * construct the trace using virtual methods
     * \return Trace object
     */
    void writeTrace(Trace * trace) const;




private:
     QIODevice * mDevice;
};

#endif // ABSTRACTTRACEWRITER_H
