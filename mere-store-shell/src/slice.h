#ifndef SLICE_H
#define SLICE_H

#include "mere/store/index/index.h"

#include <QObject>

class Slice : public QObject
{
    Q_OBJECT
public:
    explicit Slice(QObject *parent = nullptr);
    explicit Slice(const QString &store, const QString &slice, QObject *parent = nullptr);

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
    QString m_slice;
};

#endif // SLICE_H
