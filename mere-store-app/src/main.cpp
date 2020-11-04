#include "storeapp.h"

int main(int argc, char *argv[])
{
    StoreApp app(argc, argv);
    app.init();
    app.start();
    return app.exec();
}

