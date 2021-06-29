#include "mainwindow.h"
#include "localcountcodeWidget.h"
#include "gitcountcodeWidget.h"
#include "StyleButton.h"

#include <DMenu>
#include <DFrame>

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
    , m_centralWidget(new QStackedWidget(this))
{
    m_titlebar = this->titlebar();
    m_titlebar->setDisableFlags(Qt::WindowMinimizeButtonHint
                              | Qt::WindowMaximizeButtonHint
                              | Qt::WindowSystemMenuHint);
    m_titlebar->setAutoHideOnFullscreen(true);
    m_titlebar->setIcon(QIcon::fromTheme("code_count"));
    m_titlebar->setTitle("代码行数统计工具");

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    m_localButton = new StyleButton(tr("本地代码统计"), this);
    m_localButton->setChecked(true);
    m_gitButton = new StyleButton(tr("git代码统计"), this);
    buttonGroup->addButton(m_localButton, 0);
    buttonGroup->addButton(m_gitButton, 1);

    m_titlebar->addWidget(m_localButton, Qt::AlignLeft);
    m_titlebar->addWidget(m_gitButton, Qt::AlignLeft);

    LocalCountCodeWidget *localCountCodeWidget = new LocalCountCodeWidget(this);
    GitCountCodeWidget *gitCountCodeWidget = new GitCountCodeWidget(this);
    m_centralWidget->addWidget(localCountCodeWidget);
    m_centralWidget->addWidget(gitCountCodeWidget);
    setCentralWidget(m_centralWidget);

    connect(buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), [=](int index){
        m_centralWidget->setCurrentIndex(index);
    });
}

