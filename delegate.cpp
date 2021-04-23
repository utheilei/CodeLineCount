#include "delegate.h"

#include <DApplicationHelper>
#include <DApplication>
#include <DStyle>

DWIDGET_USE_NAMESPACE

HeightDelegate::HeightDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

HeightDelegate::~HeightDelegate()
{
}

void HeightDelegate::setHeight(int height)
{
    m_height = height;
}

QSize HeightDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    return QSize(size.width(), m_height);
}

void HeightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setOpacity(1);

    QStyleOptionViewItem opt = option;

    // 初始化样式
    initStyleOption(&opt, index);

    QWidget *wnd = DApplication::activeWindow();
    DPalette::ColorGroup group;
    if (!(opt.state & DStyle::State_Enabled)) {
        group = DPalette::Disabled;
    } else {
        if (!wnd) {
            group = DPalette::Inactive;
        } else {
            group = DPalette::Active;
        }
    }

    DStyle *style = qobject_cast<DStyle *>(DApplication::style());

    int radius = style->pixelMetric(DStyle::PM_FrameRadius, &option);
    int margin = 0;
    int textMargin = 5;

    // 设置背景色、文本色
    DApplicationHelper *dAppHelper = DApplicationHelper::instance();
    DPalette palette = dAppHelper->applicationPalette();
    QBrush background;
    QPen foreground;
    foreground.setColor(palette.color(group, DPalette::Text));
    if (opt.features & QStyleOptionViewItem::Alternate) {
        background = palette.color(group, DPalette::Base); // 前景色
    } else {
        background = palette.color(group, DPalette::AlternateBase); // 背景色
    }

    if (opt.state & DStyle::State_Enabled) {
        if (opt.state & DStyle::State_Selected) {
            QColor color = m_color;
            if (!color.isValid()) {
                DPalette palette;
                color = palette.brush(DPalette::Highlight).color();
            }

            background = color;
            foreground.setColor(palette.color(group, DPalette::HighlightedText));
        } else if (opt.state & DStyle::State_MouseOver) {
            background = palette.brush(DPalette::Button).color();
        }
    }

    painter->setPen(foreground);

    QRect rect = opt.rect;
    QPainterPath path;
    QPainterPath clipPath;
    QRect textRect = rect;
    // 绘制背景（圆角）
    switch (opt.viewItemPosition) {
    case QStyleOptionViewItem::Beginning: {
        rect.setX(rect.x() + margin); // 左边距
        QPainterPath rectPath;
        QPainterPath roundedPath;
        roundedPath.addRoundedRect(rect.x(), rect.y(), rect.width() * 2, rect.height(), radius, radius);
        rectPath.addRect(rect.x() + rect.width(), rect.y(), rect.width(), rect.height());
        clipPath = roundedPath.subtracted(rectPath);
        painter->setClipPath(clipPath);
        path.addRect(rect);
    } break;
    case QStyleOptionViewItem::Middle: {
        path.addRect(rect);
    } break;
    case QStyleOptionViewItem::End: {
        rect.setWidth(rect.width() - margin); // 右边距
        QPainterPath rectPath;
        QPainterPath roundedPath;
        roundedPath.addRoundedRect(rect.x() - rect.width(), rect.y(), rect.width() * 2, rect.height(), radius, radius);
        rectPath.addRect(rect.x() - rect.width(), rect.y(), rect.width(), rect.height());
        clipPath = roundedPath.subtracted(rectPath);
        painter->setClipPath(clipPath);
        path.addRect(rect);
    } break;
    case QStyleOptionViewItem::OnlyOne: {
        rect.setX(rect.x() + margin); // 左边距
        rect.setWidth(rect.width() - margin); // 右边距
        path.addRoundedRect(rect, radius, radius);
    } break;
    default: {
        painter->restore();
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    }

    painter->fillPath(path, background);

    // 绘制图标
    QRect iconRect = rect;
    QSize iconSize = QSize(0, 0);
    QVariant iconVar = index.data(Qt::DecorationRole);
    if (iconVar.isValid()) {
        QIcon icon = iconVar.value<QIcon>();
        iconSize = QSize(22, 22);

        iconRect.setX(rect.x() + 10);
        iconRect.setY(rect.y() + (iconRect.height() - iconSize.height()) / 2);
        iconRect.setHeight(iconSize.height());
        iconRect.setWidth(iconSize.width());
        icon.paint(painter, iconRect, Qt::AlignCenter);
    }

    // 绘制文本
    QFontMetrics font(opt.font);
    textRect = rect;
    textRect.setX(textRect.x() + 10 + textMargin + iconSize.width());
    QString text = font.elidedText(opt.text, opt.textElideMode, textRect.width());
    painter->drawText(textRect, Qt::TextSingleLine | static_cast<int>(opt.displayAlignment), text);

    painter->restore();
}

void HeightDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    option->showDecorationSelected = true;
    bool ok = false;
    if (index.data(Qt::TextAlignmentRole).isValid()) {
        uint value = index.data(Qt::TextAlignmentRole).toUInt(&ok);
        option->displayAlignment = static_cast<Qt::Alignment>(value);
    }

    if (!ok)
        option->displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;

    option->textElideMode = Qt::ElideRight;
    option->features = QStyleOptionViewItem::HasDisplay;
    if (index.row() % 2 == 0)
        option->features |= QStyleOptionViewItem::Alternate;

    if (index.data(Qt::DisplayRole).isValid())
        option->text = index.data().toString();
}
