#include "exploreview.h"
#include "searchview.h"
#include "listview.h"
#include "detailview.h"

#include <QSplitter>
#include <QVBoxLayout>

ExploreView::~ExploreView()
{

}

ExploreView::ExploreView(QWidget *parent)
    : QWidget(parent),
      m_seachView(nullptr),
      m_listView(nullptr),
      m_detailView(nullptr)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, Qt::transparent);
    palette.setColor(QPalette::Window, Qt::transparent);
    setAutoFillBackground(true);
    setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);
    layout->setAlignment(Qt::AlignTop);

    initUI();
}

void ExploreView::initUI()
{
    m_seachView = new SearchView(this);
    layout()->addWidget(m_seachView);

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    splitter->setHandleWidth(8);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(splitter);

    m_listView = new ListView(this);
    splitter->addWidget(m_listView);

    m_detailView = new DetailView(this);
    splitter->addWidget(m_detailView);
}
