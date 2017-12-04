#ifndef ABSTRACTSEQUENCETRACE_H
#define ABSTRACTSEQUENCETRACE_H
#include <QtCore>
#include "sequence.h"
class AbstractSequenceTrace
{
public:
    explicit AbstractSequenceTrace(QIODevice * device);

    /*!
     * \brief traces
     * \return trace vector for each nucleotids
     */
    virtual const QHash<QChar, QVector<int>>& traces() const = 0;
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
    virtual const QVector<int>& confScores()const  = 0;


    /*!
     * \brief traceLength
     * \return the length of the trace
     */
    int traceLength();
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



protected:
    QIODevice * device();
    void addComment(const QString& key, const QVariant& value);
    void clearComments();

private:
    QIODevice * mDevice;
    QHash<QString, QVariant> mComments;


};

#endif // ABSTRACTSEQUENCETRACE_H
