#include "linereader.h"

LineReader::LineReader(QObject *parent)
    : Reader(parent)
{

}

QString LineReader::read()
{
    char ch;
    do {
        qDebug() << ">>>>";
        ch = getchar();
        qDebug() << ">>>>" << ch;
        ch = getchar();
    } while (ch != QChar::LineFeed);
}
