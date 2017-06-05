#ifndef TESTVIEW_H
#define TESTVIEW_H
#include <QtWidgets>
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

    // data
    QHash< QString, QVector<QPointF>> mLineSeries;
    int mXSize = 0; // max X
    int mYSize = 0; // max Y

    // scaling
    float mYFactor = 0.2;
    float mXFactor = 1;

    // scrolling
    int mXStart = 0;

};

#endif // TESTVIEW_H
