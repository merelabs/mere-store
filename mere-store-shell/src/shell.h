#ifndef MERESTORECLI_H
#define MERESTORECLI_H

#include <QCoreApplication>

class Prompt;
class Context;

class Shell : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Shell(int argc, char *argv[]);

    bool init();
    bool start();

    static Context* context();

private:
    Prompt *m_prompt;
};

#endif // MERESTORECLI_H
