#ifndef SLICE_H
#define SLICE_H

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

    bool set(const QVariant &value);
    bool set(const QString &key, const QVariant &value);
    QVariant get(const QString &key);
    QVariant del(const QString &key);

    QVariant list();


private:
    QString m_store;
    QString m_slice;
};

#endif // SLICE_H
