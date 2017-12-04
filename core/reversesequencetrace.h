#ifndef REVERSESEQUENCETRACE_H
#define REVERSESEQUENCETRACE_H

#include "abstractsequencetrace.h"

class ReverseSequenceTrace : public AbstractSequenceTrace
{
public:
    ReverseSequenceTrace(QIODevice * device);

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
};

#endif // REVERSESEQUENCETRACE_H
