#include "countcodeWidget.h"
#include "treeview.h"

#include <QVBoxLayout>
#include <QFileIconProvider>
#include <QFile>
#include <QFileInfo>

CountCodeWidget::CountCodeWidget(QWidget *parent)
    : QWidget(parent)
    , m_treeView(new TreeView(this))
    , m_bottomWidget(new QWidget(this))
{
}

CountCodeWidget::~CountCodeWidget()
{
}

void CountCodeWidget::initUi()
{
    initForm();
    initBottomWidget();
    setLabelStyle();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addWidget(m_treeView);
    mainLayout->addWidget(m_bottomWidget);

    onClearData();
}

void CountCodeWidget::initForm()
{
}

void CountCodeWidget::initBottomWidget()
{
}

void CountCodeWidget::setLabelStyle()
{
}

void CountCodeWidget::onClearData()
{
}

QIcon CountCodeWidget::getIcon(QString filename)
{
    QFileInfo file_info(filename);
    QFileIconProvider file_icon;
    QIcon icon = file_icon.icon(file_info);
    return icon;
}

QString CountCodeWidget::getElidedText(QFont font, QString str, int MaxWidth)
{
    if (str.isEmpty())
        return "";

    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);

    if (width >= MaxWidth)
        str = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);

    return str;
}

