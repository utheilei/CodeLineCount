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
