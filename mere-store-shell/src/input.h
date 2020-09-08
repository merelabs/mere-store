#ifndef INPUT_H
#define INPUT_H

#include "processor.h"

#include <QDebug>

class Input : public Processor
{
    Q_OBJECT
public:
    ~Input();
    explicit Input(const QString &input, QObject *parent = nullptr);
    bool process() override;

//private:
    QString command() const;
    QString argument() const;
};

#endif // INPUT_H
