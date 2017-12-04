#include "sequencehighlighter.h"
#include "tracecolor.h"
SequenceHighlighter::SequenceHighlighter(QTextDocument *document)
    :QSyntaxHighlighter(document)
{

}

void SequenceHighlighter::highlightBlock(const QString &text)
{


    for (const QChar& base : TraceColor::bases())
    {
        QTextCharFormat myClassFormat;
        myClassFormat.setForeground(TraceColor::color(base).darker());

        QString reg = QString(base);
        QRegularExpression expression(reg);
        QRegularExpressionMatchIterator i = expression.globalMatch(text);
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();
            setFormat(match.capturedStart(), match.capturedLength(), myClassFormat);
        }


    }
}
