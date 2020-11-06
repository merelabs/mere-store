#include "pkgsearchview.h"

#include "../mere-store-cli/src/store.h"
#include "../mere-store-cli/src/slice.h"

#include "mere/utils/stringutils.h"

#include <QMenu>
#include <QPushButton>
#include <QActionGroup>
#include <QHBoxLayout>

SearchView::~SearchView()
{

}

SearchView::SearchView(QWidget *parent) : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, Qt::transparent);
    palette.setColor(QPalette::Window, Qt::white    );
    setAutoFillBackground(true);
    setPalette(palette);

    setMinimumHeight(64);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);

    initUI();
}

void SearchView::initUI()
{
    m_btnStore = new QPushButton(QIcon(":/store/icons/database.svg"), "Churkut", this);
    m_btnStore->setFlat(true);
    m_btnStore->setIconSize(QSize(16, 16));
    layout()->addWidget(m_btnStore);

    QMenu *menu = new QMenu(this);
    m_btnStore->setMenu(menu);

    QAction *store = new QAction(QIcon(":/store/icons/database.svg"), "Churkut", this);
    QAction *slice = new QAction(QIcon(":/store/icons/server.svg"), "Note", this);

    menu->addAction(store);
    menu->addAction(slice);

    m_btnStore->addAction(store);

    m_searchText = new QLineEdit();
    layout()->addWidget(m_searchText);

    QPushButton *more = new QPushButton(QIcon(":/store/icons/ellipsis-v.svg"), "", this);
    more->setObjectName("MoreSearchOption");
    more->setFlat(true);
    more->setIconSize(QSize(16, 16));
    more->setAccessibleName("MoreSearchOption");

    layout()->addWidget(more);

    QMenu *moreMenu = new QMenu(this);
    more->setMenu(moreMenu);

    QActionGroup *matchPosition = new QActionGroup(this);
    matchPosition->setExclusive(true);

    QAction *option1 = new QAction(QIcon(":/store/icons/database.svg"), "Start with", this);
    option1->setCheckable(true);

    QAction *option2 = new QAction(QIcon(":/store/icons/server.svg"), "End with", this);
    option2->setCheckable(true);

    QAction *option3 = new QAction(QIcon(":/store/icons/server.svg"), "Contains", this);
    option3->setCheckable(true);

    matchPosition->addAction(option1);
    matchPosition->addAction(option2);
    matchPosition->addAction(option3);

    QActionGroup *matchCase = new QActionGroup(this);
    matchCase->setExclusive(true);

    QAction *option4 = new QAction(QIcon(":/store/icons/server.svg"), "Case sensetive", this);
    option4->setCheckable(true);

    QAction *option5 = new QAction(QIcon(":/store/icons/server.svg"), "Case insensetive", this);
    option5->setCheckable(true);

    matchCase->addAction(option4);
    matchCase->addAction(option5);

    moreMenu->addAction(option1);
    moreMenu->addAction(option2);
    moreMenu->addAction(option3);
    moreMenu->addSeparator();
    moreMenu->setSeparatorsCollapsible(true);
    moreMenu->addAction(option4);
    moreMenu->addAction(option5);


    connect(m_searchText, SIGNAL(returnPressed()), this, SLOT(search()));
}

void SearchView::search()
{
    QVariant list;

    QString store = "board";
    QString slice = "tag";

    if(Mere::Utils::StringUtils::isBlank(slice))
    {
        Store s(store);
        list = s.list();
    }
    else
    {
        Slice s(store, slice);
        list = s.list();
    }

    QMap<QString, QVariant> map = list.toMap();
    QMapIterator<QString, QVariant> it(map);
    while (it.hasNext())
    {
        it.next();
        QString key = it.key();
        QString val = it.value().toString();

    }

        qDebug() << "RESULT::" << list;
//    return list;
}

void SearchView::setStore(const QString &store)
{
    m_store = store;

    m_btnStore->setText(store);
}

