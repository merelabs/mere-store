#ifndef INPUT_H
#define INPUT_H

#include "processor.h"

#include <QDebug>

class Input : public Processor
{
    Q_OBJECT
public:
    explicit Input(const QString &input, QObject *parent = nullptr);
    bool process() override;

//private:
    QString command() const;
    QString argument() const;

signals:

private:

};

#endif // INPUT_H
