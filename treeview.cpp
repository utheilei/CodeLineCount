#include "treeview.h"
#include "delegate.h"
#include "headerview.h"

#include <DApplication>
#include <DApplicationHelper>
#include <DFontSizeManager>
#include <DStyle>
#include <DIconButton>

#include <QVBoxLayout>
#include <QHeaderView>

TreeView::TreeView(QWidget *parent)
    : DTreeView(parent)
{
    initUI();
    retranslateUI();
    setMouseTracking(true);
}

void TreeView::initUI()
{
    HeightDelegate *delegate = new HeightDelegate(this);
    m_headView = new HeaderView(Qt::Horizontal, this);
    setHeader(m_headView);
    setItemDelegate(delegate);
    setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem); // 设置垂直滚动模式
    setFrameShape(QFrame::NoFrame); // 无边框设置
    setSelectionMode(QAbstractItemView::ExtendedSelection); // 设置支持多行选择（shift/ctrl）
    setSelectionBehavior(QAbstractItemView::SelectRows); // 设置点击选中整行
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setRootIsDecorated(false); // 设置降序
    setItemsExpandable(false); // 可展开项
    viewport()->setAutoFillBackground(false);
    setSortingEnabled(true);
}

void TreeView::retranslateUI()
{
}

void TreeView::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setOpacity(1);
    painter.setClipping(true);
    //根据窗口激活状态设置颜色
    QWidget *wnd = DApplication::activeWindow();
    DPalette::ColorGroup cg;
    if (!wnd) {
        cg = DPalette::Inactive;
    } else {
        cg = DPalette::Active;
    }

    auto *dAppHelper = DApplicationHelper::instance();
    auto palette = dAppHelper->applicationPalette();
    QBrush bgBrush(palette.color(cg, DPalette::Base));
    //绘制背景
    QStyleOptionFrame option;
    initStyleOption(&option);
    QRect rect = viewport()->rect();
    QRectF clipRect(rect.x(), rect.y() - rect.height(), rect.width(), rect.height() * 2);
    QRectF subRect(rect.x(), rect.y() - rect.height(), rect.width(), rect.height());
    QPainterPath clipPath, subPath;
    clipPath.addRect(rect);
    painter.fillPath(clipPath, bgBrush);
    painter.restore();
    DTreeView::paintEvent(event);
}

void TreeView::keyPressEvent(QKeyEvent *event)
{
    DTreeView::keyPressEvent(event);

    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
        emit clicked(currentIndex());
}

void TreeView::setHeaderVisble(bool visible)
{
    m_headView->setVisible(visible);
}

void TreeView::updateConent()
{
    updateGeometries();
}

int TreeView::viewRowHeight()
{
    if (this->model()->rowCount() <= 0)
        return 0;

    return this->rowHeight(this->model()->index(0, 0));
}

QModelIndexList TreeView::selectedViewIndexes()
{
    return selectedIndexes();
}
