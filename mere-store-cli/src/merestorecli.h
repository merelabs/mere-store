#ifndef MERESTORECLI_H
#define MERESTORECLI_H

#include <QEvent>
#include <QCoreApplication>

class MereCli : public QCoreApplication
{
    Q_OBJECT
public:
    explicit MereCli(int argc, char *argv[]);

    bool init();
    bool start();

    virtual bool eventFilter(QObject *object, QEvent *event)override;

};

#endif // MERESTORECLI_H
