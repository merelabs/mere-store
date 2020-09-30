#include "shell.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "Hellow!";
    Shell shell(argc, argv);
    shell.init();
    shell.start();
    return shell.exec();
}

