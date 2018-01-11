#ifndef SCFTRACEWRITER_H
#define SCFTRACEWRITER_H
#include "abstracttracewriter.h"
#include "scfheader.h"
#define SCF_MAGIC (((((quint32)'.'<<8)+(quint32)'s'<<8) \
                       +(quint32)'c'<<8)+(quint32)'f')

class ScfTraceWriter : public AbstractTraceWriter
{
public:
    ScfTraceWriter(QIODevice * device);

    virtual void writeDatas(const QHash<QChar, QVector<int>>& datas) override;
    /*!
     * \brief baseCalls
     * \return Sequence.
     * \todo should be a Sequence
     */
    virtual void writeSequence(const Sequence& sequence)  override ;
    /*!
     * \brief baseLocations
     * \return base location in trace coordinate
     */
    virtual void writeBaseLocations(const QVector<int>& locations) override;
    /*!
     * \brief confScores
     * \return confident score for each basecalls
     */
    virtual void writeBaseScores(const QVector<int>& scores )  override;
    /*!
     * \brief metadatas
     * can be empty
     * \return metadata
     */
    virtual void writeMetadatas(const QHash<QString, QVariant>& meta) override;

    void writeHeader(const ScfHeader& header);

    virtual void writeTrace(Trace * trace) override;

    ScfHeader computeHeader(Trace * trace);


};

#endif // SCFTRACEWRITER_H
