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

#ifndef ABIFREADER_H
#define ABIFREADER_H
#include <QtCore>
#include <QString>

/*!
 * \file abifreader.h
 * \brief Reader for Applied Biosystems Genetic Analyisis Data file format
 * \author Sacha Schutz
 * \version 0.1
 */

class AbifReader;
class AbifDir;
//================================================================================================

class AbifDir{
      /*! \class AbifDir
       * \brief A simple structure to store Directory Item
       *
       *  See http://www6.appliedbiosystems.com/support/software_community/ABIF_File_Format.pdf
       */
public:
    AbifDir();
    QString name;
    qint32 number;
    qint16 elementType;
    qint16 elementsize;
    qint32 numElements;
    qint32 dataSize;
    qint32 dataOffset;
    qint32 dataHandle;
    qint32 offset;
};

//================================================================================================

class AbifReader
{
    /*! \class AbifReader
     * \brief The main class to use for read Abif file.
     *
     * You can read all file which follow the abif file format specification, like ab1 or fsa file.
     * See http://www6.appliedbiosystems.com/support/software_community/ABIF_File_Format.pdf
     */
public:
    /*!
      *  \brief Constructor
      *  \param QIOdevice : input device
      */
    AbifReader(QIODevice * device );

    /*!
      *  \brief Constructor
      *  \param filename: any supported file like ab1 or fsa
      */
    AbifReader(const QString& filename);

    /*!
      *  \brief Destructor
      */
    ~AbifReader();

    enum Type {
        Byte    = 1,
        Char    = 2,
        Word    = 3,
        Short   = 4,
        Long    = 5,
        Float   = 7,
        Double  = 8,
        Date    = 10,
        Time    = 11,
        PString = 18,
        CString = 19,
        Thumb   = 12,
        Bool    = 13,
        User    = 1024
    };

    /*!
     *  \brief version of life
     *  \return the version of abif file
     */
    int version();

    /*!
     *  \brief abif file
     *  \return True if the file is readable as abif file
     */
    bool isAbif();

    /*!
     *  \brief Directory keys
     * A key is the combinaison between the name and number of directory
     * For instance if the directory'name is "Peak" and the number is "2", the key will be "Peak.2"
     *  \return Return all avaible key from directory
     */
    QStringList directoryKeys() const;

    /*!
     *  \brief directory
     *  \param key : a combinaison between name and number of directory. ex:Name.Number
     *  \return Return directory from an existing key.
     */
    AbifDir directory(const QString& key) const;

    /*!
     *  \brief data
     *  \param key : a combinaison between name and number of directory. ex:Name.Number
     *  \return Return a QVariant data from an existing directory key.
     */
    QVariant data(const QString& key);

protected:
    /*!
     *  \brief loadData
     *  \param key : QIODevice
     *   Load data from the constructor
     */
    void loadData(QIODevice * device);
    /*!
     *  \brief directory from offset
     *  \param key : offset file position
     *   \return Return an AbifDir object
     */
    AbifDir dirFromOffset(int offset);
    /*!
     *  \brief Unserialize data directory
     *  \param key : AbifDir object
     *   \return Return an unserialized variant from a Diretory
     */
    QVariant fromDir(const AbifDir& dir);

    /*!
     *  \brief convert one item QVariantList to QVariant
     *  \param key : a QVariantList
     *   \return Return a QVariant
     */
    QVariant reduce(QVariantList& list);


    void debugDir(AbifDir dir);

private:
    QIODevice * mDevice;
    QString mAbif;
    qint16 mVersion;
    QMap<QString,AbifDir> mDirs;  // keys = name.number
    AbifDir mRootDir;
};




#endif // ABIFREADER_H
