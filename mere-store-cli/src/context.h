#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QDebug>

class Context : public QObject
{
    Q_OBJECT
public:
    explicit Context(QObject *parent = nullptr);

    static const QString Root;
    static const QString Store;
    static const QString Slice;

    QString store() const;
    QString slice() const;

public slots:
    void selected(QString value);
    void selected(QString context, QString value);

signals:

private:
    QString m_store;
    QString m_slice;

};

#endif // CONTEXT_H
