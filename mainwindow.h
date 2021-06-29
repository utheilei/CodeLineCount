#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DTitlebar>

DWIDGET_USE_NAMESPACE

class QStackedWidget;
class StyleButton;
class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:

private:
    DTitlebar *m_titlebar = Q_NULLPTR;
    StyleButton *m_localButton = Q_NULLPTR;
    StyleButton *m_gitButton = Q_NULLPTR;
    QStackedWidget *m_centralWidget = Q_NULLPTR;
};

#endif // MAINWINDOW_H
