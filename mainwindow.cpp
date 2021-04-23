#include "mainwindow.h"
#include "countcodeWidget.h"

#include <DMenu>
#include <DFrame>

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    m_titlebar = this->titlebar();
    m_titlebar->setDisableFlags(Qt::WindowMinimizeButtonHint
                              | Qt::WindowMaximizeButtonHint
                              | Qt::WindowSystemMenuHint);
    m_titlebar->setAutoHideOnFullscreen(true);
    m_titlebar->setIcon(QIcon::fromTheme("code_count"));
    m_titlebar->setTitle("代码行数统计工具");

    CountCodeWidget *countCodeWidget = new CountCodeWidget(this);
    setCentralWidget(countCodeWidget);
}

