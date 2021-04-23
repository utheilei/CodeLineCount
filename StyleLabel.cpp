#include "StyleLabel.h"

#include <DApplicationHelper>

#include <QPainter>
#include <QStyleOptionFrame>

DWIDGET_USE_NAMESPACE

StyleLabel::StyleLabel(QWidget *parent) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setFrameShape(QFrame::StyledPanel);
    setLineWidth(0);
}

void StyleLabel::setTextColor(QPalette::ColorRole color)
{
    DApplicationHelper *dAppHelper = DApplicationHelper::instance();
    DPalette palette = dAppHelper->applicationPalette();
    QPalette labelPalette = this->palette();
    labelPalette.setColor(QPalette::WindowText, palette.color(color));
    setPalette(labelPalette);
}

void StyleLabel::setTextColor(const QColor &color)
{
    QPalette labelPalette = this->palette();
    labelPalette.setColor(QPalette::WindowText, color);
    setPalette(labelPalette);
}

void StyleLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStyleOptionFrame opt;
    initStyleOption(&opt);
    QPainter p(this);

    const DPalette &dp = DApplicationHelper::instance()->palette(this);
    p.setBackground(dp.brush(QPalette::Button));
    p.setPen(QPen(dp.frameBorder(), opt.lineWidth));
    style()->drawControl(QStyle::CE_ShapedFrame, &opt, &p, this);

    QLabel::paintEvent(event);
}

void StyleLabel::initStyleOption(QStyleOptionFrame *option) const
{
    QFrame::initStyleOption(option);

    option->features |= QStyleOptionFrame::Rounded;
}
