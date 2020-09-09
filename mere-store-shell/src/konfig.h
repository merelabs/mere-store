#ifndef KONFIG_H
#define KONFIG_H

#include <QObject>

class Konfig : public QObject
{
    Q_OBJECT
public:
    explicit Konfig(QObject *parent = nullptr);

    QString get(const QString &key) const;
    bool set(const QString &key, const QString &values) const;

signals:

};

#endif // KONFIG_H
