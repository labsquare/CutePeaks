#ifndef REVERSESEQUENCETRACE_H
#define REVERSESEQUENCETRACE_H

#include "abstracttracereader.h"

class ReverseSequenceProxyTrace : public AbstractTraceReader
{
public:
    ReverseSequenceProxyTrace(AbstractTraceReader * source);

    /* \brief traces
    * \return trace vector for each nucleotids
    */
   virtual const QHash<QChar, QVector<int>>& datas() const;
   /*!
    * \brief baseCalls
    * \return Sequence.
    * \todo should be a Sequence
    */
   virtual const Sequence& sequence()const;
   /*!
    * \brief baseLocations
    * \return base location in trace coordinate
    */
   virtual const QVector<int>& baseLocations()const;
   /*!
    * \brief confScores
    * \return confident score for each basecalls
    */
   virtual const QVector<int>& baseScores()const;


private:
    AbstractTraceReader * mSource;

    QHash<QChar, QVector<int>> mTraces;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    Sequence mBaseCalls;

};

#endif // REVERSESEQUENCETRACE_H
