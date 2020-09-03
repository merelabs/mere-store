#ifndef READER_H
#define READER_H

#include <QObject>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = nullptr);

    virtual QString read() = 0;

signals:
    void read(QChar &);
    void read(QString &);
};

#endif // READER_H
