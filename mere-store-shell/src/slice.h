#ifndef SLICE_H
#define SLICE_H

#include "mere/store/store/pairstore.h"
#include "mere/store/index/index.h"

#include <QObject>

class Slice : public QObject
{
    Q_OBJECT
public:
    explicit Slice(const QString &store, const QString &slice, QObject *parent = nullptr);

    bool create() const;
    bool select() const;
    bool close() const;
    bool remove() const;

    bool create(const Mere::Store::Index &index) const;

    bool set(const QVariant &value, const QString &type);
    bool set(const QString &key, const QVariant &value, const QString &type);

    QVariant get(const QString &key) const;
    QVariant get(const QList<QString> &keys) const;

    bool del(const QString &key) const;
    bool del(const QList<QString> &keys) const;

    QVariant list();
    QVariant list(const uint &limit);
    QVariant list(const QString &key);
    QVariant list(const QString &key, const uint &limit);

private:
    Mere::Store::PairStore *slice(const QString &type) const;

private:
    QString m_store;
    QString m_slice;
};

#endif // SLICE_H
