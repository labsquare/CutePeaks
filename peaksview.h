#ifndef PEAKSVIEW_H
#define PEAKSVIEW_H
#include <QtWidgets>
#include "PeaksWidget.h"

class PeaksView : public QScrollArea
{
    Q_OBJECT
public:
    PeaksView(QWidget * parent = 0);
    PeaksWidget * widget();
    void setFilename(const QString& filename);

public Q_SLOTS:
    void setAmplitudeFactor(int factor);
    void setScaleFactor(int factor);

private:
    PeaksWidget * mWidget;
};

#endif // PEAKSVIEW_H
