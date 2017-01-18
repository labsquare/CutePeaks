// AbifReader
//Copyright (C) 2015 labsquare.org
// Author : Schutz Sacha

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "abifreader.h"
#include <byteswap.h>

AbifDir::AbifDir()
{
    number= -1;
    elementType= -1;
    elementsize= -1;
    numElements= -1;
    dataSize= -1;
    dataOffset= -1;
    dataHandle= -1;
}
//----------------------------------------------------------------
AbifReader::AbifReader(QIODevice *device)
{
    loadData(device);
}
//----------------------------------------------------------------

AbifReader::AbifReader(const QString &filename)
{
    QFile * file  = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug()<<Q_FUNC_INFO<<"cannot read file";
        delete file;
        return;
    }

    loadData(file);
}
//----------------------------------------------------------------

AbifReader::~AbifReader()
{
    mDevice->close();
    mDirs.clear();
}
//----------------------------------------------------------------

int AbifReader::version()
{
    return mVersion;
}
//----------------------------------------------------------------

bool AbifReader::isAbif()
{
    if (mAbif.toLower() == "abif")
        return true;
    else
        return false;
}
//----------------------------------------------------------------

QStringList AbifReader::directoryKeys() const
{
    return mDirs.keys();
}
//----------------------------------------------------------------

AbifDir AbifReader::directory(const QString &key) const
{
    if (mDirs.contains(key))
        return mDirs.value(key);
    else {
        qDebug()<<Q_FUNC_INFO<<"cannot find directory key";
        return AbifDir();
    }
}

//----------------------------------------------------------------


QVariant AbifReader::data(const QString &key)
{
    if (!mDirs.contains(key))
        return QVariant();

    AbifDir dir = directory(key);
    return fromDir(dir);
}
//----------------------------------------------------------------
QVariant AbifReader::fromDir(const AbifDir &dir)
{
    // Try to unserialize all data ! Not sure if all is working
    // Check specification from http://www6.appliedbiosystems.com/support/software_community/ABIF_File_Format.pdf

    //debugDir(dir);
    QByteArray part;


    if (dir.dataSize<=4){

        int val = dir.dataOffset;
        val = __bswap_32(val);
        char * data = (char*)&val;
        part.setRawData(data,dir.dataSize);

    }
    else {
        mDevice->seek(dir.dataOffset);
        part = mDevice->read(dir.dataSize);

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

        if (dir.name == "Scal")
        {
            qDebug()<<dir.elementsize;
        }

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

    return QVariant(-1);
}
//----------------------------------------------------------------
QVariant AbifReader::reduce(QVariantList &list)
{
    if (list.count() == 1)
        return list.first();
    else return QVariant::fromValue(list);
}

//----------------------------------------------------------------

void AbifReader::loadData(QIODevice *device)
{
    mDevice = device;

    // Read abif
    mDevice->seek(0);
    mAbif = mDevice->read(4);

    if (!isAbif())
        return;
    // Read version
    mDevice->seek(4);
    mVersion = qFromBigEndian<qint16>((uchar*)(mDevice->read(2).data()));

    // load Root dictionnary
    mRootDir = dirFromOffset(6);

    // load All dictionnaries
    for (int i = 0; i < mRootDir.numElements; ++i) {

        AbifDir dir = dirFromOffset(mRootDir.dataOffset + i * 28);
        QString key = QString("%1.%2").arg(dir.name).arg(dir.number);
        mDirs.insert(key, dir);




    }





}
//----------------------------------------------------------------

AbifDir AbifReader::dirFromOffset(int offset)
{
    AbifDir dir;
    mDevice->seek(offset);
    dir.name = mDevice->read(4);

    dir.number      = qFromBigEndian<qint32>((uchar*)(mDevice->read(4).data()));
    dir.elementType = qFromBigEndian<qint16>((uchar*)(mDevice->read(2).data()));
    dir.elementsize = qFromBigEndian<qint16>((uchar*)(mDevice->read(2).data()));
    dir.numElements = qFromBigEndian<qint32>((uchar*)(mDevice->read(4).data()));
    dir.dataSize    = qFromBigEndian<qint32>((uchar*)(mDevice->read(4).data()));
    dir.dataOffset  = qFromBigEndian<qint32>((uchar*)(mDevice->read(4).data()));
    dir.dataHandle  = qFromBigEndian<qint32>((uchar*)(mDevice->read(4).data()));

    // my custom
    dir.offset      = offset;





    return dir;


}



//----------------------------------------------------------------

void AbifReader::debugDir(AbifDir dir)
{
    qDebug()<<"name"<<dir.name;
    qDebug()<<"number"<<dir.number;
    qDebug()<<"type"<<dir.elementType;
    qDebug()<<"e.size"<<dir.elementsize;
    qDebug()<<"e.num"<<dir.numElements;
    qDebug()<<"data size"<<dir.dataSize;
    qDebug()<<"data offset"<<dir.dataOffset;
    qDebug()<<"data handle"<<dir.dataHandle;
    qDebug()<<"offset"<<dir.offset;

}
