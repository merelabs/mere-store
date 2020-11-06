#include "selectview.h"
#include "../mere-store-cli/src/store.h"

#include <QFont>
#include <QLabel>
#include <QScreen>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

SelectView::SelectView(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QString::fromUtf8("MereStoreSelectView"));
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, Qt::red);
    palette.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(25, 50, 25, 25);
    layout->setSpacing(30);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    initUI();
}

void SelectView::initUI()
{
    //initHeaderUI();

    QWidget *logo = new QWidget(this);
    layout()->addWidget(logo);

    QVBoxLayout *logoLayout = new QVBoxLayout(logo);
    logoLayout->setContentsMargins(0, 0, 0, 0);
    logoLayout->setSpacing(0);

    QPushButton *button = new QPushButton(this);
    button->setIconSize(QSize(72, 72));
    button->setIcon(QIcon(":/store/icons/database.svg"));
    button->setFlat(true);
    logoLayout->addWidget(button);

    QLabel *label = new QLabel("store");
    label->setMinimumWidth(64);
    label->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(label);

    QWidget *prompt = new QWidget(this);
    prompt->setMaximumWidth(width()/2);
    this->layout()->addWidget(prompt);

    QVBoxLayout *promptLayout = new QVBoxLayout(prompt);
    promptLayout->setContentsMargins(3, 3, 3, 3);
    promptLayout->setSpacing(3);

    QLabel *promptLabel = new QLabel(tr("Name:"));
    promptLayout->addWidget(promptLabel);

    m_name = new QLineEdit(this);
    promptLayout->addWidget(m_name);

    QLabel *baseLabel = new QLabel(tr("path:/tmp/store"));
    promptLayout->addWidget(baseLabel);

    QFont font = baseLabel->font();
    font.setPointSize(6);
    baseLabel->setFont(font);

    QPalette palette = baseLabel->palette();;
    palette.setColor(QPalette::WindowText, QColor(0, 0, 0, 50));
    baseLabel->setPalette(palette);

    QWidget *footer = new QWidget(this);
    layout()->addWidget(footer);

    QVBoxLayout *footerLayout = new QVBoxLayout(footer);
    footerLayout->setContentsMargins(3, 50, 3, 3);
    footerLayout->setSpacing(3);
    footerLayout->setAlignment(Qt::AlignCenter);

    QPushButton *select = new QPushButton(tr("Connect"), this);
    select->setObjectName("Connect");
//    connect->setIcon(QIcon(":/store/icons/database.svg"));
//    connect->setFlat(true);
    select->setMinimumWidth(200);
//    connect->setMaximumWidth(200);
    footerLayout->addWidget(select);

    connect(select, SIGNAL(clicked(bool)), this, SLOT(select()));


}

void SelectView::initHeaderUI()
{
    QWidget *logo = new QWidget(this);
    logo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout()->addWidget(logo);

    QVBoxLayout *logoLayout = new QVBoxLayout(logo);
    logoLayout->setContentsMargins(5, 15, 15, 5);
    logoLayout->setSpacing(0);
    logoLayout->setAlignment(Qt::AlignRight);

    QPushButton *button = new QPushButton(this);
    button->setIconSize(QSize(24, 24));
    button->setIcon(QIcon(":/widgets/icons/times-circle.svg"));
    button->setFlat(true);
    logoLayout->addWidget(button);
}

void SelectView::select()
{
    qDebug() << "Select store:" << m_name->text();

    Store store(m_name->text());
    bool ok = store.select();
    if (!ok)
    {
        qDebug() << "Failed to select store:" << m_name->text();
        return;
    }
    emit selected(m_name->text());
}

void SelectView::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)

    QScreen *screen = QApplication::primaryScreen();
    QRect rect = screen->availableGeometry();

    QSize size(700, 400);

    resize(size);

    move(rect.center() - QPoint(size.width()/2, size.height()/2));
}

