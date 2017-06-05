#include "AbifSequenceTrace.h"


AbifSequenceTrace::AbifSequenceTrace(QIODevice *device)
    :AbstractSequenceTrace(device)
{
    loadData();
}

int AbifSequenceTrace::version() const
{
    return mVersion;
}

QStringList AbifSequenceTrace::keys() const
{
    return mDirs.keys();
}

QVariant AbifSequenceTrace::data(const QString &key)
{
    if (!mDirs.contains(key))
        return QVariant();

    return fromDir(mDirs[key]);
}

void AbifSequenceTrace::readDictionnaries()
{
    if (device()->open(QIODevice::ReadOnly))
    {
        // reset device
        device()->seek(0);
        // read magic
        QString magic  = device()->read(4);

        if (magic.toUpper() != "ABIF")
            qCritical()<<"Not an ABIF FILE";

        // read version
        mVersion = qFromBigEndian<qint16>((uchar*)(device()->read(2).data()));

        // Load Root dictionnarie
        mRootDir = dirFromOffset(6);

        // Load all dictionnaries
        for (int i = 0; i < mRootDir.numElements; ++i) {
            AbifDir dir = dirFromOffset(mRootDir.dataOffset + i * 28);
            QString key = QString("%1.%2").arg(dir.name).arg(dir.number);
            mDirs.insert(key, dir);
        }
    }
}

void AbifSequenceTrace::readTraces()
{
    // read base order
    QString baseorder = data("FWO_.1").toString();

    // read traces
    // DATA between 9-12 will contain the processed data.
    int start = 9;
    for (int i=start; i< start + baseorder.size()  ; ++i)
    {
        QString key = QString("DATA.%1").arg(i);
        QVector<int> trace;
        for ( QVariant val : data(key).toList())
            trace.append(val.toInt());

        setTrace(baseorder[i-start], trace);
    }
}

void AbifSequenceTrace::readBaseCalls()
{
    setBaseCalls(data("PBAS.1").toByteArray());
}

void AbifSequenceTrace::readBaseLocations()
{
    QVector<int> locations;
    for ( QVariant v : data("PLOC.1").toList())
        locations.append(v.toInt());

    setBaseLocations(locations);

}

void AbifSequenceTrace::readConfScores()
{
    QVector<int> locations;

    for ( QVariant v : data("PCON.1").toString()){
        locations.append(v.toInt());
    }
    setConfScores(locations);
}

bool AbifSequenceTrace::loadData()
{
    readDictionnaries();
    readTraces();
    readBaseCalls();
    readBaseLocations();
    readConfScores();

    return true;
}


AbifDir AbifSequenceTrace::dirFromOffset(int offset)
{
    AbifDir dir;
    device()->seek(offset);
    dir.name = device()->read(4);

    dir.number      = qFromBigEndian<qint32>((uchar*)(device()->read(4).data()));
    dir.elementType = qFromBigEndian<qint16>((uchar*)(device()->read(2).data()));
    dir.elementsize = qFromBigEndian<qint16>((uchar*)(device()->read(2).data()));
    dir.numElements = qFromBigEndian<qint32>((uchar*)(device()->read(4).data()));
    dir.dataSize    = qFromBigEndian<qint32>((uchar*)(device()->read(4).data()));
    dir.dataOffset  = qFromBigEndian<qint32>((uchar*)(device()->read(4).data()));
    dir.dataHandle  = qFromBigEndian<qint32>((uchar*)(device()->read(4).data()));

    // my custom
    dir.offset      = offset;

    return dir;

}

QVariant AbifSequenceTrace::fromDir(const AbifDir &dir)
{
    // Try to unserialize all data ! Not sure if all is working
    // Check specification from http://www6.appliedbiosystems.com/support/software_community/ABIF_File_Format.pdf

    QByteArray part;

    if (dir.dataSize<=4){

        int val = dir.dataOffset;
        val = qToBigEndian(val);
        char * data = (char*)&val;
        part.setRawData(data,dir.dataSize);
    }

    else {
        device()->seek(dir.dataOffset);
        part = device()->read(dir.dataSize);
    }

    QDataStream stream(part);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    stream.setByteOrder(QDataStream::BigEndian);

    //-----------------------------------------------
    if (Type(dir.elementType) == CString ) // 19
    {
        part.chop(1);
        return QString(part);
    }
    //-----------------------------------------------

    if (Type(dir.elementType) == PString ) // 18
    {
        part.remove(0,1);
        return QString(part);
    }
    //-----------------------------------------------

    if (Type(dir.elementType) == Word ) // 3
        return QString(part);
    //-----------------------------------------------

    if (Type(dir.elementType) == Char ) // 2
        return QString(part);
    //-----------------------------------------------

    if (Type(dir.elementType) == Short ) // 4
    {
        QVariantList list;
        qint16 v;
        while (!stream.atEnd())
        {
            stream >> v;
            list.append(v);
        }
        return reduce(list);
    }
    //-----------------------------------------------

    if (Type(dir.elementType) == Date ) // 10
    {
        QVariantList list;
        while (!stream.atEnd())
        {
            qint16 year;
            quint8 month;
            quint8 day;

            stream >> year;
            stream >> month;
            stream >> day;

            QDate date = QDate();
            date.setDate(year,month,day);
            list.append(date);
        }

        return reduce(list);
    }
    //-----------------------------------------------

    if (Type(dir.elementType) == Time ) // 11
    {
        QVariantList list;
        while (!stream.atEnd())
        {
            quint8 hour    = 0;
            quint8 minute  = 0;
            quint8 second  = 0;
            quint8 hsecond = 0;

            stream>>hour;
            stream>>minute;
            stream>>second;
            stream>>hsecond;
            qDebug()<<hour;  // HUGE BUG... IF I remove this, QTime won't be set
            QTime time(hour,minute,second,hsecond);
            list.append(time);
        }
        return reduce(list);
    }
    //-----------------------------------------------
    if (Type(dir.elementType) == Float ) // 7
    {
        QVariantList list;
        float v;
        while (!stream.atEnd())
        {
            stream >> v;
            list.append(v);
        }
        return reduce(list);
    }
    //-----------------------------------------------
    if (Type(dir.elementType) == Long ) // 5
    {
        QVariantList list;
        qint32 v;

        while (!stream.atEnd())
        {
            stream >> v;
            list.append(v);
        }
        return reduce(list);
    }

    return QVariant();
}

QVariant AbifSequenceTrace::reduce(QVariantList &list)
{
    if (list.count() == 1)
        return list.first();
    else return QVariant::fromValue(list);
}



