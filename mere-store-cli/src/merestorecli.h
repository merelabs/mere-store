#ifndef MERESTORECLI_H
#define MERESTORECLI_H

//#include <QEvent>
#include <QCoreApplication>

class Prompt;
class Context;

class MereCli : public QCoreApplication
{
    Q_OBJECT
public:
    explicit MereCli(int argc, char *argv[]);

    bool init();
    bool start();

//    virtual bool eventFilter(QObject *object, QEvent *event) override;

    static Context* context();

private:
    Prompt *m_prompt;
//    Context *m_context;

};

#endif // MERESTORECLI_H
