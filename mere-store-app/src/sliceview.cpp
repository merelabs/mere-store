#include "sliceview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

SliceView::~SliceView()
{

}

SliceView::SliceView(const QString &store, const QString &slice, QWidget *parent)
    : QWidget(parent),
      m_store(store),
      m_slice(slice)
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

void SliceView::initUI()
{
    initHeaderUI();
    initContentUI();
}

void SliceView::initHeaderUI()
{
    QWidget *header = new QWidget(this);
    layout()->addWidget(header);

    QHBoxLayout *layout = new QHBoxLayout(header);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);

    QPushButton *m_btnStore = new QPushButton(QIcon(":/store/icons/server.svg"), m_slice, this);
    m_btnStore->setFlat(true);
    m_btnStore->setIconSize(QSize(32, 32));
    layout->addWidget(m_btnStore);

    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addSpacerItem(spacer);
}

void SliceView::initContentUI()
{
    QWidget *slices = new QWidget(this);
    layout()->addWidget(slices);

    QHBoxLayout *layout = new QHBoxLayout(slices);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);

    QPushButton *btnHeader = new QPushButton(QIcon(":/store/icons/server.svg"), "Indexes", this);
    btnHeader->setFlat(true);
    btnHeader->setIconSize(QSize(32, 32));
    layout->addWidget(btnHeader);

    QSpacerItem *spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addSpacerItem(spacer);

    QPushButton *btnCreate = new QPushButton(QIcon(":/store/icons/plus.svg"), "", this);
    btnCreate->setFlat(true);
    btnCreate->setIconSize(QSize(24, 24));
    layout->addWidget(btnCreate);
}
