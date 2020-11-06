#ifndef STOREVIEW_H
#define STOREVIEW_H

#include <QWidget>

class SliceView : public QWidget
{
    Q_OBJECT
public:
    ~SliceView();
    explicit SliceView(const QString &store, const QString &slice, QWidget *parent = nullptr);

private:
    void initUI();
    void initHeaderUI();
    void initContentUI();

signals:

private:
    QString m_store;
    QString m_slice;
};

#endif // STOREVIEW_H
