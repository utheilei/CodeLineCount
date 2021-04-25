#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include <QHeaderView>

class HeaderView : public QHeaderView
{
    Q_OBJECT

public:
    HeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);

    QSize sizeHint() const override;
    int sectionSizeHint(int logicalIndex) const;

    inline int getSpacing() const { return m_spacing; }
    inline void setSpacing(int spacing) { m_spacing = spacing; }

signals:
    void headerViewMouseMove();

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    int m_spacing = 1;
    Qt::FocusReason m_reson;
};

#endif // HEADERVIEW_H
