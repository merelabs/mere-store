#ifndef MDEL_H
#define MDEL_H

#include "../command.h"

class MDel : public Command
{
    Q_OBJECT
public:
    explicit MDel(QObject *parent = nullptr);
    explicit MDel(QString argument,  QObject *parent = nullptr);

    bool execute() const override;
};
#endif // MDEL_H
