#ifndef STORE_H
#define STORE_H

#include <QObject>
#include <QDebug>

class MereStore;

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

    bool set(const QVariant value);
    bool set(const QString key, const QVariant value);
    QVariant get(const QString key);
    QVariant del(const QString &key);

    QVariant list();

private:
    QString m_store;
};

#endif // STORE_H
