#include "shell.h"

int main(int argc, char *argv[])
{
    qDebug() <<"HELLOW";
    Shell shell(argc, argv);
    shell.init();
    shell.start();
    return shell.exec();
}

