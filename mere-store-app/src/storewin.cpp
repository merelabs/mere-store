#include "storewin.h"
#include "storepanel.h"
#include "exploreview.h"
#include "storeview.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QStackedWidget>

StoreWin::~StoreWin()
{

}

StoreWin::StoreWin(QWidget *parent)
    : Mere::Widgets::ResizeableWin(parent)
{
    setObjectName("MereStoreAppWin");

    layout()->setContentsMargins(2, 2, 2, 2);
    layout()->setSpacing(3);


     initUI();
}

void StoreWin::init()
{

}

void StoreWin::initHeaderUI()
{
    m_header = new Mere::Widgets::SimpleWinHeaderEx(this);
    m_header->initUI();
    m_header->setTitle("Mere Store Explorer");
    layout()->addWidget(m_header);

    connect(m_header, SIGNAL(closed()), this, SIGNAL(closed()));
}

void StoreWin::initContentUI()
{
    QWidget *m_centralWidget = new QWidget(this);
    layout()->addWidget(m_centralWidget);

    QHBoxLayout *hLayout = new QHBoxLayout(m_centralWidget);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(3);

    m_panel = new StorePanel(this);
    hLayout->addWidget(m_panel);

    QWidget *widget = new QWidget(this);
    hLayout->addWidget(widget);

    QVBoxLayout *vLayout = new QVBoxLayout(widget);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(3);

    QSplitter *contentWidget = new QSplitter(this);
    contentWidget->setHandleWidth(8);
    contentWidget->setObjectName("SplitterWidget");

    m_stackView = new QStackedWidget;
    connect(m_stackView, SIGNAL(currentChanged(int)), this, SLOT(boardChanged(int)));
    contentWidget->addWidget(m_stackView);
    vLayout->addWidget(contentWidget);

    ExploreView *exploreView = new ExploreView(this);
    m_stackView->addWidget(exploreView);

    StoreView *storeView = new StoreView("abc");
    m_stackView->addWidget(storeView);
    m_stackView->setCurrentWidget(storeView);

    m_statusbar = new Mere::Widgets::StatusBar(this);
    vLayout->addWidget(m_statusbar);

    connect(m_panel, &StorePanel::selected, [=](const QString &store){
        exploreView->setStore(store);
    });
}

void StoreWin::initFooterUI()
{

}
