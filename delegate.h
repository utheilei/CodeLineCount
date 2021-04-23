//界面样式处理，主界面的行高、可编辑列、圆角、颜色、可编辑列的代理

#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>

class HeightDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit HeightDelegate(QObject *parent = Q_NULLPTR);
    ~HeightDelegate() Q_DECL_OVERRIDE;

    // 设置行高（默认 30）
    void setHeight(int height);

    // 缺省大小
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    // 自绘
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    // 初始样式选项
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    int m_height = 36;
    QColor m_color;
};

#endif // DELEGATE_H
