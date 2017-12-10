#ifndef SEQUENCETRACEFACTORY_H
#define SEQUENCETRACEFACTORY_H
#include <QtCore>
#include "abifsequencetrace.h"
#include "scfsequencetrace.h"
#include "trace.h"

class TraceFactory
{
public:
    enum FileType{
        Unknown,
        ZTR,
        ABIF,
        SCF
    };

    /*!
     * \brief filetype
     * \param device
     * \return type according magic number from binary file
     */
    static FileType filetype(QIODevice * device);
    /*!
     * \brief filetype
     * \param filename
     * @see filetype(QIODevice * device)
     * \return return type from filname.
     */
    static FileType filetype(const QString& filename);

    /*!
     * \brief createTrace
     * \param filename
     * Create Tracefile from any supported file
     * \return Trace object
     */
    static Trace * createTrace(const QString& filename);




private:
    TraceFactory(){}
};

#endif // SEQUENCETRACEFACTORY_H
