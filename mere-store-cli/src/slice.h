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

signals:

private:
    QString m_store;
    QString m_slice;
};

#endif // SLICE_H
