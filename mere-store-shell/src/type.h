#ifndef TYPE_H
#define TYPE_H

#include <QObject>

class Type : public QObject
{
    Q_OBJECT
public:
    explicit Type(QObject *parent = nullptr);
    bool create();
    bool remove();

signals:

};

#endif // TYPE_H
