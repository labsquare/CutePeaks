#include "PeaksCalling.h"
#include <numeric>

PeaksCalling::PeaksCalling(QHash<QChar, QVector<int>> * traces) : m_traces(traces)
{

}



void PeaksCalling::compute_value()
{
    //If job are do didn't do it again
    if(value_computed)
        return ;

    // Compute derivation for each series
    this->generate_derivate_series();

    // Call peaks position
    this->call_peaks_position();

    // Generate sequence

    // Compute Phread score
}

void PeaksCalling::generate_derivate_series()
{
    QChar tmp[4] = {'A', 'C', 'T', 'G'};
    for(auto base : tmp)
    {
        this->m_deriv_traces[base] = QVector<double>();
        std::adjacent_difference((*this->m_traces)[base].begin(),
                                 (*this->m_traces)[base].end(),
                                 std::back_inserter(this->m_deriv_traces[base]),
                                 [](int a, int b){return (a-b)/2.0;});
    }
}

void PeaksCalling::call_peaks_position()
{
    auto itA = (*this->m_traces)['A'].begin();
    auto itC = (*this->m_traces)['C'].begin();
    auto itG = (*this->m_traces)['T'].begin();
    auto itT = (*this->m_traces)['G'].begin();

    auto const itAbegin = (*this->m_traces)['A'].begin();
    auto const itCbegin = (*this->m_traces)['C'].begin();
    auto const itGbegin = (*this->m_traces)['T'].begin();
    auto const itTbegin = (*this->m_traces)['G'].begin();

    auto const itAend = (*this->m_traces)['A'].end();
    auto const itCend = (*this->m_traces)['C'].end();
    auto const itGend = (*this->m_traces)['T'].end();
    auto const itTend = (*this->m_traces)['G'].end();

    while(true)
    {
        if(itA == itAend && itC == itCend && itT == itTend && itG == itGend)
            break;

        if((itA != itAbegin || itA != itAend) && *std::prev(itA) > *itA)
            m_base_locations.push_back(itA - itAbegin);

        if((itC != itCbegin || itC != itCend) && *std::prev(itC) > *itC)
            m_base_locations.push_back(itC - itCbegin);

        if((itG != itGbegin || itG != itGend) && *std::prev(itG) > *itG)
            m_base_locations.push_back(itG - itGbegin);

        if((itT != itTbegin || itT != itTend) && *std::prev(itT) > *itT)
            m_base_locations.push_back(itT - itTbegin);

        if(itA != itAend)
            itA++;
        if(itC != itCend)
            itC++;
        if(itG != itGend)
            itG++;
        if(itT != itTend)
            itT++;
    }
}

Sequence PeaksCalling::sequence()
{
    this->compute_value();

    return m_base_calls;
}

QVector<int> PeaksCalling::confScores()
{
    this->compute_value();

    return m_conf_scores;
}

QVector<int> PeaksCalling::baseLocations()
{
    this->compute_value();

    return m_base_locations;
}

