#ifndef ALIAS_H
#define ALIAS_H

#include <QObject>

class Alias : public QObject
{
    Q_OBJECT
public:
    explicit Alias(QObject *parent = nullptr);

signals:

};

#endif // ALIAS_H
