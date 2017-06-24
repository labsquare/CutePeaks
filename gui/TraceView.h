#ifndef TESTVIEW_H
#define TESTVIEW_H
#include <QtWidgets>
#include <QScroller>
#include "SequenceTraceFactory.h"
#include "AbifSequenceTrace.h"

struct Selection
{
    int pos;
    int length;
};

class TraceView : public QAbstractScrollArea
{
public:
    TraceView(QWidget * parent = 0);
    void setFilename(const QString& filename);

    AbstractSequenceTrace * sequenceTrace();

    bool isValid() const;

public Q_SLOTS:
    void setAmplitudeFactor(float factor);
    void setScaleFactor(float factor);
    void setSelection(int pos, int length = 1);

protected :
    void paintEvent(QPaintEvent * event)  Q_DECL_OVERRIDE;
    void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * event)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * event);
    bool viewportEvent(QEvent * event) Q_DECL_OVERRIDE;
    virtual void setupViewport();
    bool inView(int pos, int margin = 0);

    void updateScrollbar();

    void drawConfident(QPainter& painter);
    void drawBases(QPainter& painter);
    void drawAminoAcid(QPainter& painter);
    void drawTraces(QPainter& painter);
    void drawSelection(QPainter& painter);


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

    Selection mCurrentSelection = { 20, 10};


};

#endif // TESTVIEW_H
