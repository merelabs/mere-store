#include "app.h"

#include "kvutils.h"

int main(int argc, char *argv[])
{
    App app(argc, argv);
    app.init();
    app.start();

    return app.exec();
}

