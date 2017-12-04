#ifndef SEQUENCEHIGHLIGHTER_H
#define SEQUENCEHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextFormat>
#include "tracecolor.h"


class SequenceHighlighter : public QSyntaxHighlighter
{
public:
    SequenceHighlighter(QTextDocument * document);

    void highlightBlock(const QString& text);
};

#endif // SEQUENCEHIGHLIGHTER_H
