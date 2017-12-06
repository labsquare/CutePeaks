#ifndef ABSTRACTSEQUENCETRACE_H
#define ABSTRACTSEQUENCETRACE_H
#include <QtCore>
#include "sequence.h"
#include "trace.h"

class Trace;
class AbstractTraceReader;
class AbstractTraceReader
{
public:
    explicit AbstractTraceReader(QIODevice * device);
    virtual ~AbstractTraceReader();

    /*!
     * \brief traces
     * \return trace vector for each nucleotids
     */
    virtual const QHash<QChar, QVector<int>>& datas() const = 0;
    /*!
     * \brief baseCalls
     * \return Sequence.
     * \todo should be a Sequence
     */
    virtual const Sequence& sequence()const  = 0 ;
    /*!
     * \brief baseLocations
     * \return base location in trace coordinate
     */
    virtual const QVector<int>& baseLocations()const  = 0;
    /*!
     * \brief confScores
     * \return confident score for each basecalls
     */
    virtual const QVector<int>& baseScores()const  = 0;
    /*!
     * \brief metadatas
     * can be empty
     * \return metadata
     */
    virtual const QHash<QString, QVariant>& metadatas() const = 0;


    /*!
     * \brief createTrace
     * construct the trace using virtual methods
     * \return Trace object
     */
    Trace createTrace() const;

protected:
    QIODevice * device();


private:
    QIODevice * mDevice;


};

#endif // ABSTRACTSEQUENCETRACE_H
