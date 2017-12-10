#include "tracecolor.h"

QHash<QChar, QColor> TraceColor::colorsHash = {
    {'A',QColor("#009000")},    // green
    {'C',QColor("#0000ff")},    // blue
    {'G',QColor("#000000")},    // black
    {'T',QColor("#ff0000")},    // red
    {'W',QColor("#804800")},    // mix of A and T
    {'S',QColor("#000080")},    // mix of C and G
    {'M',QColor("#004880")},    // mix of A and C
    {'K',QColor("#800000")},    // mix of G and T
    {'R',QColor("#004800")},    // mix of A and G
    {'Y',QColor("#800080")},    // mix of C and T
    {'B',QColor("#550055")},    // mix of C, G, and T
    {'D',QColor("#553000")},    // mix of A, G, and T
    {'H',QColor("#553055")},    // mix of A, C, and T
    {'V',QColor("#003055")},    // mix of A, C, and G
    {'N',QColor("#999")}        // gray
};

