#ifndef LINEREADER_H
#define LINEREADER_H

#include "reader.h"

class LineReader : public Reader
{
    Q_OBJECT
public:
    explicit LineReader(QObject *parent = nullptr);
    QString read() override;

signals:

};

#endif // LINEREADER_H
