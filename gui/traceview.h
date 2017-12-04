#ifndef TESTVIEW_H
#define TESTVIEW_H
#include <QtWidgets>
#include <QScroller>
#include <QSvgGenerator>
#include "SequenceTraceFactory.h"
#include "AbifSequenceTrace.h"
#include "tracecolor.h"

struct Selection
{
    int pos;
    int length;
};

class TraceView : public QAbstractScrollArea
{
    Q_OBJECT
public:
    TraceView(QWidget * parent = 0);
    /*!
     * \brief setFilename
     * \param filename
     * Load a trace file
     */
    void setFilename(const QString& filename);

    /*!
     * \brief sequenceTrace
     * \return the trace sequence object
     */
    AbstractSequenceTrace * sequenceTrace();

    /*!
     * \brief isValid
     * \return true is the sequence is valid and has been loaded
     */
    bool isValid() const;

    bool toSvg(const QString& filename);
    bool toPng(const QString& filename);


public Q_SLOTS:
    void setAmplitudeFactor(float factor);
    void setScaleFactor(float factor);
    void setSelection(int pos, int length = 1);

protected :
    void paintEvent(QPaintEvent * event)  override;
    void scrollContentsBy(int dx, int dy) override;
    void resizeEvent(QResizeEvent * event)override;
    void mouseMoveEvent(QMouseEvent * event) override;
    bool viewportEvent(QEvent * event) override;
    void setupViewport();

    /*!
     * \brief inView
     * \param pos
     * \param margin
     * \return true if the position is in the viewport according margin
     */
    bool inView(int pos, int margin = 0);

    void updateScrollbar();

    void drawAll(QPainter& painter);

    /*!
     * \brief drawConfident
     * \param painter
     * Draw confident score as a rect blue path
     */
    void drawConfident(QPainter& painter);
    /*!
     * \brief drawBases
     * \param painter
     * draw nucleotid text on the top of the trace
     */
    void drawBases(QPainter& painter);
    /*!
     * \brief drawAminoAcid
     * \param painter
     * draw amino acid text on the top of the trace
     */
    void drawAminoAcid(QPainter& painter);
    /*!
     * \brief drawTraces
     * \param painter
     * Draw all traces from AbstractSequenceTrace
     */
    void drawTraces(QPainter& painter);
    /*!
     * \brief drawSelection
     * \param painter
     * Draw selection
     */
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
    QScroller * mScroller;

    Selection mCurrentSelection = { 20, 10};


};

#endif // TESTVIEW_H
