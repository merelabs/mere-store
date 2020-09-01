#include "merestorecli.h"

#include "kvutils.h"

int main(int argc, char *argv[])
{
    MereCli app(argc, argv);
    app.init();
    app.start();

    return app.exec();
}

