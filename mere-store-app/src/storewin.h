#ifndef STOREWIN_H
#define STOREWIN_H

#include "mere/widgets/resizeablewin.h"
#include "mere/widgets/simplewinheaderex.h"
#include "mere/widgets/statusbar.h"

#include <QStackedWidget>
class StoreWin : public Mere::Widgets::ResizeableWin
{
    Q_OBJECT
public:
    ~StoreWin();
    explicit StoreWin(QWidget *parent = nullptr);

    void init();

protected:
    void initHeaderUI();
    void initContentUI();
    void initFooterUI();

signals:
    void closed();

private:
    Mere::Widgets::SimpleWinHeaderEx *m_header;
    Mere::Widgets::StatusBar *m_statusbar;

    QStackedWidget *m_stackView;
};

#endif // STOREWIN_H
