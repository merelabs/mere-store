#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>

class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(const QString &input, QObject *parent = nullptr);
    virtual bool process() = 0;

    const QString input() const;

signals:

private:
    const QString &m_input;
};

#endif // PROCESSOR_H
