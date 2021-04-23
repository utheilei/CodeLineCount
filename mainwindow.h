#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DTitlebar>

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:

private:
    DTitlebar *m_titlebar = Q_NULLPTR;
};

#endif // MAINWINDOW_H
