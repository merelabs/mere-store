#include "storeview.h"
#include "createview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

StoreView::~StoreView()
{

}

StoreView::StoreView(const QString &store, QWidget *parent)
    : QWidget(parent),
      m_store(store)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, Qt::transparent);
    palette.setColor(QPalette::Window, Qt::white    );
    setAutoFillBackground(true);
    setPalette(palette);

    setMinimumHeight(64);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);
    layout->setAlignment(Qt::AlignTop);

    initUI();
}

void StoreView::initUI()
{
    initHeaderUI();
    initContentUI();
}

void StoreView::initHeaderUI()
{
    QWidget *header = new QWidget(this);
    layout()->addWidget(header);

    QHBoxLayout *layout = new QHBoxLayout(header);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);

    QPushButton *m_btnStore = new QPushButton(QIcon(":/store/icons/database.svg"), m_store, this);
    m_btnStore->setFlat(true);
    m_btnStore->setIconSize(QSize(32, 32));
    layout->addWidget(m_btnStore);

    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addSpacerItem(spacer);
}

void StoreView::initContentUI()
{
    QWidget *slices = new QWidget(this);
    layout()->addWidget(slices);

    QHBoxLayout *layout = new QHBoxLayout(slices);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);

    QPushButton *btnHeader = new QPushButton(QIcon(":/store/icons/server.svg"), "Slices", this);
    btnHeader->setFlat(true);
    btnHeader->setIconSize(QSize(32, 32));
    layout->addWidget(btnHeader);

    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addSpacerItem(spacer);

    QPushButton *btnCreate = new QPushButton(QIcon(":/store/icons/plus.svg"), "", this);
    btnCreate->setFlat(true);
    btnCreate->setIconSize(QSize(24, 24));
    layout->addWidget(btnCreate);

    connect(btnCreate, &QPushButton::clicked, [=](){
        CreateView *createView  = new CreateView(&m_store);
        createView->show();

        connect(createView, &CreateView::created, [=](){
            createView->hide();
            createView->disconnect();
            createView->deleteLater();
        });
    });
}


