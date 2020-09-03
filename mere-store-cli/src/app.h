#ifndef MERESTORECLI_H
#define MERESTORECLI_H

#include <QCoreApplication>

class Prompt;
class Context;

class App : public QCoreApplication
{
    Q_OBJECT
public:
    explicit App(int argc, char *argv[]);

    bool init();
    bool start();

    static Context* context();

private:
    Prompt *m_prompt;
};

#endif // MERESTORECLI_H
