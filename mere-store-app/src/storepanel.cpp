#include "storepanel.h"
#include "selectview.h"
#include "createview.h"

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

StorePanel::~StorePanel()
{
    if (m_selectView)
    {
        delete m_selectView;
        m_selectView = nullptr;
    }
}

StorePanel::StorePanel(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("MereStoreDockPanel"));
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    setMaximumWidth(64);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(0, 46, 99));
    setAutoFillBackground(true);
    setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    initUI();
}

void StorePanel::initUI()
{
    QPushButton *btnSelect = addControl(QIcon(":/store/icons/database.svg"));
    connect(btnSelect, SIGNAL(clicked(bool)), this, SLOT(select()));


    QPushButton *btnCreate = addControl(QIcon(":/store/icons/plus.svg"));
    connect(btnCreate, SIGNAL(clicked(bool)), this, SLOT(create()));

//    initSearchPanel();

//    initSwitchBoard();

    QPushButton *btnSettings = addControl(QIcon(":/store/icons/tools.svg"));
    connect(btnSettings, SIGNAL(clicked(bool)), this, SLOT(showAdminPanel()));

    QPushButton *btnHelp = addControl(QIcon(":/store/icons/question.svg"));
    connect(btnHelp, SIGNAL(clicked(bool)), this, SLOT(showHelp()));

    QPushButton *btnIcon = addControl(QIcon(":/store/icons/logo.svg"));

////    switchBoard();
}

QPushButton* StorePanel::addControl(const QIcon &icon)
{
    QPushButton *control = new QPushButton(icon, "", this);
    control->setFlat(true);
    control->setIconSize(QSize(24, 24));

    layout()->addWidget(control);

    return control;
}

void StorePanel::select()
{
    m_selectView  = new SelectView;
    m_selectView->show();

    connect(m_selectView, &SelectView::selected, [=](const QString &store){
        m_selectView->hide();
        m_selectView->disconnect();
        m_selectView->deleteLater();
        emit selected(store);
    });
}

void StorePanel::create()
{
    m_createView  = new CreateView;
    m_createView->show();

    connect(m_createView, &CreateView::created, [=](){
        m_createView->hide();
        m_createView->disconnect();
        m_createView->deleteLater();
    });
}
