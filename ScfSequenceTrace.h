#ifndef SCFSEQUENCETRACE_H
#define SCFSEQUENCETRACE_H
#include "AbstractSequenceTrace.h"
#include <limits>
struct ScfHeader
{
        quint32 magic_number;
        quint32 samples;          /* Number of elements in Samples matrix */
        quint32 samples_offset;   /* Byte offset from start of file */
        quint32 bases;            /* Number of bases in Bases matrix */
        quint32 bases_left_clip;  /* OBSOLETE: No. bases in left clip (vector) */
        quint32 bases_right_clip; /* OBSOLETE: No. bases in right clip (qual) */
        quint32 bases_offset;     /* Byte offset from start of file */
        quint32 comments_size;    /* Number of bytes in Comment section */
        quint32 comments_offset;  /* Byte offset from start of file */
        char version[4];         /* "version.revision", eg '3' '.' '0' '0' */
        quint32 sample_size;      /* Size of samples in bytes 1=8bits, 2=16bits*/
        quint32 code_set;         /* code set used (may be ignored) */
        quint32 private_size;     /* No. of bytes of Private data, 0 if none */
        quint32 private_offset;   /* Byte offset from start of file */
        quint32 spare[18];        /* Unused */
};



class ScfSequenceTrace : public AbstractSequenceTrace
{
public:
    ScfSequenceTrace(QIODevice * device);

    const QHash<QChar, QVector<int>>& traces() const override;
    const QByteArray& sequence()const  override;
    const QVector<int>& baseLocations()const  override;
    const QVector<int>& confScores()const  override;

    QByteArray version() const;

protected:
    bool load();

    void readHeader();
    void readComments();
    void readBases();
    template <typename T>
    void readTraces();
    template<typename T>
    void decodeDelta(QVector<T>& data);



private:
    ScfHeader mHeader;
    // store data
    QHash<QChar, QVector<int>> mTraces;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    QByteArray mBaseCalls;
    QIODevice * mDevice;

    QHash<QChar, QList<quint8>> mTempProba;

};

#endif // SCFSEQUENCETRACE_H
