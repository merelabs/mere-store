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

    QString get() const;

public slots:
    void selected(QString context);

signals:

private:
    QString m_context;

};

#endif // CONTEXT_H
