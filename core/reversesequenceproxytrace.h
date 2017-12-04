#ifndef REVERSESEQUENCETRACE_H
#define REVERSESEQUENCETRACE_H

#include "abstractsequencetrace.h"

class ReverseSequenceProxyTrace : public AbstractSequenceTrace
{
public:
    ReverseSequenceProxyTrace(AbstractSequenceTrace * source);

    /* \brief traces
    * \return trace vector for each nucleotids
    */
   virtual const QHash<QChar, QVector<int>>& traces() const;
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
   virtual const QVector<int>& confScores()const;


private:
    AbstractSequenceTrace * mSource;

    QHash<QChar, QVector<int>> mTraces;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    Sequence mBaseCalls;

};

#endif // REVERSESEQUENCETRACE_H
