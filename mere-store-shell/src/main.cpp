#include "shell.h"
#include "kvutils.h"

int main(int argc, char *argv[])
{
    Shell shell(argc, argv);
    shell.init();
    shell.start();
    return shell.exec();
}

