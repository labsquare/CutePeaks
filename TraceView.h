#ifndef TESTVIEW_H
#define TESTVIEW_H
#include <QtWidgets>
#include <QScroller>
#include "SequenceTraceFactory.h"
#include "AbifSequenceTrace.h"

class TraceView : public QAbstractScrollArea
{
public:
    TraceView(QWidget * parent = 0);
    void setFilename(const QString& filename);

    AbstractSequenceTrace * sequenceTrace();

public Q_SLOTS:
    void setAmplitudeFactor(float factor);
    void setScaleFactor(float factor);

protected :
    void paintEvent(QPaintEvent * event)  Q_DECL_OVERRIDE;
    void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event);
    bool viewportEvent(QEvent * event) Q_DECL_OVERRIDE;
    virtual void setupViewport();

    void updateScrollbar();

private:

    QString mFilename;
    AbstractSequenceTrace * mSequenceTrace = nullptr;

    // data
    QHash< QString, QVector<QPointF>> mLineSeries;

    // scaling
    float mYFactor = 0.1;
    float mXFactor = 2;

    // scrolling
    int mXStart = 0;

    // qc bar
    float mQCHeightFactor = 1.4;
    int mQCWidth = 10;

    // trace colors
    QHash<QChar, QColor> mTraceColors;

    QScroller * mScroller;


};

#endif // TESTVIEW_H
