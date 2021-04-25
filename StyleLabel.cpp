/*
* Copyright (C) 2021 ~ 2030 Uniontech Software Technology Co.,Ltd.
*
* Author:     helei <helei@uniontech.com>
*
* Maintainer: helei <helei@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    QPainter painter(this);

    const DPalette &dpalette = DApplicationHelper::instance()->palette(this);
    painter.setBackground(dpalette.brush(QPalette::Button));
    painter.setPen(QPen(dpalette.frameBorder(), opt.lineWidth));
    style()->drawControl(QStyle::CE_ShapedFrame, &opt, &painter, this);

    QLabel::paintEvent(event);
}

void StyleLabel::initStyleOption(QStyleOptionFrame *option) const
{
    QFrame::initStyleOption(option);

    option->features |= QStyleOptionFrame::Rounded;
}
