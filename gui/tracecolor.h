#ifndef TRACECOLOR_H
#define TRACECOLOR_H
#include <QtCore>
#include <QColor>

class TraceColor
{
public:
    static QColor color(const QChar& base) {
        return colorsHash.value(base, Qt::black);
    }
    static QList<QChar> bases(){
        return TraceColor::colorsHash.keys();
    }

    static QHash<QChar, QColor> colorsHash;

};






#endif // TRACECOLOR_H
