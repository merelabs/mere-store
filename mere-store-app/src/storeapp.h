#ifndef STOREAPP_H
#define STOREAPP_H

#include "mere/widgets/defaultapp.h"
#include "mere/store/config/config.h"

namespace Mere
{
    namespace Store
    {
        #ifdef APP_CODE
        const QString AppCode   = APP_CODE;
        #else
        const QString AppCode   = "store";
        #endif

        #ifdef APP_NAME
        const QString AppName   = APP_NAME;
        #else
        const QString AppName   = "mere-store";
        #endif

        #ifdef APP_VERSION
        const QString AppVersion= APP_VERSION;
        #else
        const QString AppVersion= "0.0.0b";
        #endif
    }
}

class StoreWin;
class StoreApp : public Mere::DefaultApp
{
    Q_OBJECT
public:
    ~StoreApp();
    explicit StoreApp(int &argc, char **argv);

    void init();
    void start();

    static Mere::Store::Config* config();

signals:

private slots:
    void close();

private:
    StoreWin *m_win;
};

#endif // STOREAPP_H
