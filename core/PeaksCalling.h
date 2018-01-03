#ifndef PEAKSCALLING_H
#define PEAKSCALLING_H

#include <QtCore>
#include <QHash>
#include <QVector>
#include "sequence.h"

class PeaksCalling
{
public:
    explicit PeaksCalling(QHash<QChar, QVector<int>> * traces);

    QHash<QChar, QVector<int>>& traces();

    QVector<int> baseLocations();

    QVector<int> confScores();

    Sequence sequence();

private:
    void compute_value();

    void generate_derivate_series();
    void call_peaks_position();
private:
    bool value_computed = false;
    QHash<QChar, QVector<double>> m_deriv_traces;

    QHash<QChar, QVector<int>> * m_traces;
    QVector<int> m_base_locations;
    QVector<int> m_conf_scores;
    Sequence m_base_calls;

};

#endif // PEAKSCALLING_H
