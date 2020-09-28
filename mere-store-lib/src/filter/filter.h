#ifndef MERESTOREFILTER_H
#define MERESTOREFILTER_H

#include <QObject>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MERESTOREFILTER_H
