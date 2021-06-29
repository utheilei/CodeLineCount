#include "gitcountcodeWidget.h"
#include "treeview.h"
#include "StyleLabel.h"

#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDir>

const QStringList fileFilter = {"h", "cpp", "c"};

GitCountCodeWidget::GitCountCodeWidget(QWidget *parent)
    : CountCodeWidget(parent)
{
    initUi();
}

GitCountCodeWidget::~GitCountCodeWidget()
{
}

void GitCountCodeWidget::initForm()
{
    m_model = new QStandardItemModel(m_treeView);
    m_treeView->setModel(m_model);

    QStringList headText;
    headText << "文件名" << "类型" << "大小" << "总行数" << "新增行数" << "删除行数";
    QList<int> columnWidth;
    columnWidth << 300 << 100 << 100 << 100 << 100 << 100;

    int columnCount = headText.count();

    m_model->setHorizontalHeaderLabels(headText);
    m_model->setColumnCount(columnCount);

    for (int i = 0; i < columnCount; i++) {
        m_treeView->setColumnWidth(i, columnWidth.at(i));
    }
}

void GitCountCodeWidget::initBottomWidget()
{
    QGridLayout *layout = new QGridLayout;
    m_bottomWidget->setLayout(layout);

    QLabel *fileLabel = new QLabel("新增行数",this);
    m_fileCountLabel = new StyleLabel(this);
    m_fileCountLabel->setMinimumWidth(80);
    QLabel *sizeLabel = new QLabel("删除行数",this);
    m_sizeCountLabel = new StyleLabel(this);
    m_sizeCountLabel->setMinimumWidth(80);
    QLabel *rowsLabel = new QLabel("总行数",this);
    m_codeCountLabel = new StyleLabel(this);
    m_codeCountLabel->setMinimumWidth(80);

    QLabel *dirLabel = new QLabel("目录",this);
    dirLabel->setMinimumWidth(60);
    dirLabel->setAlignment(Qt::AlignCenter);
    QLabel *label = new QLabel("作者",this);
    label->setMinimumWidth(60);
    label->setAlignment(Qt::AlignCenter);
    QLabel *timeLabel = new QLabel("时间", this);
    timeLabel->setMinimumWidth(60);
    timeLabel->setAlignment(Qt::AlignCenter);

    m_edit = new QLineEdit(this);
    m_dirEdit = new QLineEdit(this);
    m_dirEdit->setReadOnly(true);
    m_timeEdit = new QLineEdit(this);

    DSuggestButton *openDirBtn = new DSuggestButton("打开目录", this);
    DSuggestButton *countBtn = new DSuggestButton("统计数据", this);
    DSuggestButton *clearBtn = new DSuggestButton("清除数据", this);

    layout->addWidget(fileLabel, 0 , 0);
    layout->addWidget(m_fileCountLabel, 0 , 1);
    layout->addWidget(dirLabel, 0 , 2);
    layout->addWidget(m_dirEdit, 0 , 3);
    layout->addWidget(openDirBtn, 0 , 4);
    layout->addWidget(sizeLabel, 1 , 0);
    layout->addWidget(m_sizeCountLabel, 1 , 1);
    layout->addWidget(label, 1 , 2);
    layout->addWidget(m_edit, 1 , 3);
    layout->addWidget(countBtn, 1 , 4);
    layout->addWidget(rowsLabel, 2 , 0);
    layout->addWidget(m_codeCountLabel, 2 , 1);
    layout->addWidget(timeLabel, 2 , 2);
    layout->addWidget(m_timeEdit, 2 , 3);
    layout->addWidget(clearBtn, 2 , 4);

    connect(openDirBtn, &QPushButton::clicked, this, &GitCountCodeWidget::onOpenPath);
    connect(countBtn, &QPushButton::clicked, this, &GitCountCodeWidget::onCountCode);
    connect(clearBtn, &QPushButton::clicked, this, &GitCountCodeWidget::onClearData);
}

void GitCountCodeWidget::deleteAllData()
{
    if (m_model->rowCount() <= 0)
        return;

    for (int i = m_model->rowCount() - 1; i >= 0; i--) {
        m_model->removeRow(i);
    }
}

void GitCountCodeWidget::setLabelStyle()
{
    m_fileCountLabel->setTextColor(QColor("#17A086"));
    m_codeCountLabel->setTextColor(QColor("#CA5AA6"));
    m_sizeCountLabel->setTextColor(QColor("#CD1B19"));

    QFont font;
    font.setBold(true);

    m_fileCountLabel->setFont(font);
    m_codeCountLabel->setFont(font);
    m_sizeCountLabel->setFont(font);
}

void GitCountCodeWidget::onOpenPath()
{
    QString path = QFileDialog::getExistingDirectory(this, "选择目录", "./",  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!path.isEmpty()) {
        onClearData();
        m_timeEdit->setText("2021-01-01,2021-06-30");
        m_dirEdit->setText(getElidedText(m_dirEdit->font(), path, m_dirEdit->width()));
    }
}

void GitCountCodeWidget::onClearData()
{   
    m_fileCountLabel->setText("0");
    m_sizeCountLabel->setText("0");
    m_codeCountLabel->setText("0");

    m_edit->clear();
    m_dirEdit->clear();

    deleteAllData();
}

void GitCountCodeWidget::parseFile()
{
    quint32 newLines = 0;
    quint32 deleteLines = 0;

    QString fileName = m_dirEdit->text() + "/countCode.txt";
    if (!QFile::exists(fileName))
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        qInfo() << "======" << "file open failed";
        return;
    }

    QTextStream txtInput(&file);
    QStringList lineStr;
    while (!txtInput.atEnd()) {
        lineStr = txtInput.readLine().split("\t");
        if (lineStr.size() < 3)
            continue;
        QFileInfo info(lineStr[2]);
        if (fileFilter.contains(info.suffix())) {
            addItem(info, lineStr[0].toInt(), lineStr[1].toInt());
        }

        newLines  += lineStr[0].toInt();
        deleteLines  += lineStr[1].toInt();
    }

    file.close();

    m_fileCountLabel->setText(QString::number(newLines));
    m_sizeCountLabel->setText(QString::number(deleteLines));
    m_codeCountLabel->setText(QString::number(newLines - deleteLines));
}

void GitCountCodeWidget::addItem(QFileInfo info, int newLine, int deleteLine)
{
    QStandardItem *itemName = new QStandardItem;
    itemName->setText(info.fileName());
    itemName->setIcon(getIcon(info.filePath()));

    QStandardItem *itemSuffix = new QStandardItem;
    itemSuffix->setText(info.suffix());

    QStandardItem *itemSize = new QStandardItem;
    itemSize->setText(QString::number(info.size()));

    QStandardItem *itemLine = new QStandardItem;
    itemLine->setText(QString::number(newLine - deleteLine));

    QStandardItem *itemCode = new QStandardItem;
    itemCode->setText(QString::number(newLine));

    QStandardItem *itemNote = new QStandardItem;
    itemNote->setText(QString::number(deleteLine));

    QList<QStandardItem *> listItem;
    listItem << itemName << itemSuffix << itemSize << itemLine << itemCode << itemNote;

    m_model->appendRow(listItem);
}

void GitCountCodeWidget::onCountCode()
{
    if (m_dirEdit->text().isEmpty() || m_edit->text().isEmpty() || m_timeEdit->text().isEmpty())
        return;

    QDir dir;
    dir.setCurrent(m_dirEdit->text());

    if (QFile::exists("countCode.txt"))
        QFile::remove("countCode.txt");

    QString author = m_edit->text().trimmed();
    QStringList time = m_timeEdit->text().split(",");
    if (time.size() < 2)
        return;

    QString cmd = QString("git log --author='%1' --since='%2' --until='%3' --pretty=tformat: --numstat >> %4/countCode.txt")
                  .arg(author).arg(time[0]).arg(time[1]).arg(m_dirEdit->text());

    int res = system(cmd.toLatin1().data());

    if (res != 0)
        qInfo() << "==========" << "cmd start failed";
    else
        parseFile();
}
