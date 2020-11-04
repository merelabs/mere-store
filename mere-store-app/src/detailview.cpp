#include "detailview.h"

DetailView::~DetailView()
{

}

DetailView::DetailView(QWidget *parent) : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::yellow);
    setAutoFillBackground(true);
    setPalette(palette);
    setMinimumHeight(100);
}
