#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QDebug>

class Context : public QObject
{
    Q_OBJECT
public:
    explicit Context(QObject *parent = nullptr);

    QString store() const;
    QString slice() const;

    QString context() const;

public slots:
    void switched(const QString &value);
    void selected(const QString &context, const QString &value);

private:
    QString m_store;
    QString m_slice;
};

#endif // CONTEXT_H
