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

#ifndef STYLELABEL_H
#define STYLELABEL_H

#include <QLabel>

class StyleLabel : public QLabel
{
    Q_OBJECT
public:
    explicit StyleLabel(QWidget *parent = nullptr);

    void setTextColor(QPalette::ColorRole color);

    void setTextColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void initStyleOption(QStyleOptionFrame *option) const;
};

#endif // STYLELABEL_H
