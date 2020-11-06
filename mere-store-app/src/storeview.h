#ifndef STOREVIEW_H
#define STOREVIEW_H

#include <QWidget>

class StoreView : public QWidget
{
    Q_OBJECT
public:
    ~StoreView();
    explicit StoreView(const QString &store, QWidget *parent = nullptr);

private:
    void initUI();
    void initHeaderUI();
    void initContentUI();

signals:

private:
    QString m_store;
};

#endif // STOREVIEW_H
