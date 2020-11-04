#include "listview.h"

ListView::~ListView()
{

}

ListView::ListView(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::blue);
    setAutoFillBackground(true);
    setPalette(palette);

    setMinimumHeight(100);

    qDebug() << "YES!!!";
}
