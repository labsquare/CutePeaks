#ifndef TESTVIEW_H
#define TESTVIEW_H
#include <QtWidgets>
#include "SequenceTraceFactory.h"
#include "AbifSequenceTrace.h"

class TraceView : public QAbstractScrollArea
{
public:
    TraceView(QWidget * parent = 0);
    void setFilename(const QString& filename);

public Q_SLOTS:
    void setAmplitudeFactor(float factor);
    void setScaleFactor(float factor);

protected :
    void paintEvent(QPaintEvent * event)  Q_DECL_OVERRIDE;
    void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event);
    bool viewportEvent(QEvent * event) Q_DECL_OVERRIDE;

    void load();
    void updateScrollbar();

private:

    QString mFilename;
    AbstractSequenceTrace * mSequenceTrace;

    // data
    QHash< QString, QVector<QPointF>> mLineSeries;

    // scaling
    float mYFactor = 0.2;
    float mXFactor = 3;

    // scrolling
    int mXStart = 0;

    // trace colors
    QHash<QChar, QColor> mTraceColors;

};

#endif // TESTVIEW_H
