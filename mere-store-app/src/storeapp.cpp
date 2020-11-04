#include "storeapp.h"
#include "storewin.h"

#include <QScreen>

StoreApp::~StoreApp()
{
    if (m_win)
    {
        delete m_win;
        m_win = nullptr;
    }
}

StoreApp::StoreApp(int &argc, char **argv)
    : DefaultApp(argc, argv),
      m_win(new StoreWin)
{
    setAppCode(Mere::Store::AppCode);
    setApplicationName(Mere::Store::AppName);
    setApplicationVersion(Mere::Store::AppVersion);
}

void StoreApp::init()
{
    Mere::DefaultApp::init();
    m_win->init();

    connect(m_win, SIGNAL(closed()), this, SLOT(close()));
}

void StoreApp::start()
{
    QScreen *primaryScreen = this->primaryScreen();;
    m_win->resize(primaryScreen->size());
    m_win->show();
}

void StoreApp::close()
{
    exit(0);
}


//static
Mere::Store::Config* StoreApp::config()
{
    return  Mere::Store::Config::instance();
}

