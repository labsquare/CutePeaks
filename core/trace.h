#ifndef TRACE_H
#define TRACE_H
#include <QtCore>
#include "sequence.h"

class Trace
{
public:
    Trace();


    const QHash<QChar, QVector<int>>& traces() const;
    const QVector<int>& baseLocations() const;
    const QVector<int>& confScores() const;


   const Sequence& sequence() const ;


    /*!
     * \brief traceLength
     * \return the length of the trace
     */
    int traceLengh();

    /*!
     * \brief bases
     * \return base avaible as index for trace.
     */
    QList<QChar> bases() const;

    /*!
      * \brief trace
      * \param base
      * \return Return trace vector for a specific base
      */

    QVector<int> trace(const QChar& base) const;

    /*!
      * \brief keys
      * \return comments keys
      */
    QStringList keys() const;
    /*!
      * \brief value
      * \param key
      * \return return comments value for a specific keyes
      */
    QVariant value(const QString& key);

    /*!
      * \brief isValid
      * \return true the trace is valid. Return false otherwise
      */
    bool isValid() const;


    //should be friends ?
    void setSequence(const Sequence& seq);
    void setTraces(const QHash<QChar, QVector<int>> data);
    void setBaseLocations(const QVector<int>& data);
    void setConfScores(const QVector<int>& data);




private:
    QHash<QChar, QVector<int>> mTraces;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    Sequence mBaseCalls;


};

#endif // TRACE_H
