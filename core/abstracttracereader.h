#ifndef ABSTRACTSEQUENCETRACE_H
#define ABSTRACTSEQUENCETRACE_H
#include <QtCore>
#include "sequence.h"
#include "trace.h"

class AbstractTraceReader
{
public:
    explicit AbstractTraceReader(QIODevice * device);

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


    Trace trace() const;

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




protected:
    QIODevice * device();
    void addComment(const QString& key, const QVariant& value);
    void clearComments();

private:
    QIODevice * mDevice;
    QHash<QString, QVariant> mComments;


};

#endif // ABSTRACTSEQUENCETRACE_H
