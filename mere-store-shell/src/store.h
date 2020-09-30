#ifndef STORE_H
#define STORE_H

#include "mere/store/index/index.h"

#include <QObject>
#include <QDebug>

class MereStore;
//class Mere::Store::Index;

class Store : public QObject
{
    Q_OBJECT
public:
    explicit Store(QObject *parent = nullptr);
    explicit Store(QString store, QObject *parent = nullptr);

    bool create() const;
    bool select() const;
    bool close() const;
    bool remove() const;

    bool create(const Mere::Store::Index &index) const;

    bool set(const QVariant &value);
    bool set(const QString &key, const QVariant &value);

    QVariant get(const QString &key) const;
    QVariant get(const QList<QString> &keys) const;

    bool del(const QString &key) const;
    bool del(const QList<QString> &keys) const;

    QVariant list();
    QVariant list(const uint &limit);
    QVariant list(const QString &key);
    QVariant list(const QString &key, const uint &limit);

private:
    QString m_store;
};

#endif // STORE_H
