#ifndef TRACE_H
#define TRACE_H
#include <QtCore>
#include "sequence.h"
#include "abstracttracereader.h"

class AbstractTraceReader;
class Trace;
class Trace
{
public:
    Trace(const QHash<QChar, QVector<int>> datas,
          const QVector<int>& baseLocations,
          const QVector<int>& baseScores,
          const Sequence& sequence);
    /*!
     * \brief datas
     * @example data['A'] = 3,4,5,12,224,42,52 ....
     * \return data tracein pixel for each avaible bases
     */
    const QHash<QChar, QVector<int>>& datas() const;
    /*!
     * \brief baseLocations
     * \return return peaks location in data trace coordinate
     */
    const QVector<int>& baseLocations() const;
    /*!
     * \brief baseScores
     * \return return score for each bases
     */
    const QVector<int>& baseScores() const;
    /*!
     * \brief sequence
     * \return the sequence base call
     */
    const Sequence& sequence() const ;

    /*!
     * \brief traceLength
     * \return the length of datas in pixel
     */
    int length();
    /*!
     * \brief bases
     * \return base avaible as index for trace.
     */
    QList<QChar> basesAvaible() const;
    /*!
      * \brief data
      * \param base
      * \return Return trace data ector for a specific base
      */
    QVector<int> data(const QChar& base) const;
    /*!
      * \brief keys
      * \return metadata keys
      */
    QStringList keys() const;
    /*!
      * \brief value
      * \param key
      * \return return metadata value for a specific keyes
      */
    const QVariant& value(const QString& key);

    /*!
      * \brief isValid
      * \return true the trace is valid. Return false otherwise
      */
    bool isValid() const;


private:
    QHash<QChar, QVector<int>> mDatas;
    QVector<int> mBaseLocations;
    QVector<int> mBaseScores;
    Sequence mSequence;
    QHash<QString, QVariant> mMetadatas;


};

#endif // TRACE_H
