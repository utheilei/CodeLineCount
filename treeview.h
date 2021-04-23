#ifndef REMOTEVIEW_H
#define REMOTEVIEW_H

#include <DLabel>
#include <DTreeView>

#include <QMouseEvent>

DWIDGET_USE_NAMESPACE

class HeaderView;

class TreeView : public DTreeView
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = Q_NULLPTR);

    void setHeaderVisble(bool visible);
    void updateConent();
    int viewRowHeight();
    QModelIndexList selectedViewIndexes();

private:
    void initUI();
    void retranslateUI();

public slots:

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    HeaderView *m_headView = Q_NULLPTR;
};

#endif // REMOTEVIEW_H
