#include "countcodeWidget.h"
#include "treeview.h"
#include "StyleLabel.h"

#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileIconProvider>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QtConcurrent>

const QString fileFilter = "*.h *.cpp *.c *.cs *.java *.js";

CountCodeWidget::CountCodeWidget(QWidget *parent) : QWidget(parent)
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

CountCodeWidget::~CountCodeWidget()
{
}

void CountCodeWidget::initForm()
{
    m_treeView = new TreeView(this);
    m_model = new QStandardItemModel(m_treeView);
    m_treeView->setModel(m_model);

    QStringList headText;
    headText << "文件名" << "类型" << "大小" << "总行数" << "代码行数" << "注释行数" << "空白行数";
    QList<int> columnWidth;
    columnWidth << 240 << 100 << 100 << 100 << 100 << 100 << 100;

    int columnCount = headText.count();

    m_model->setHorizontalHeaderLabels(headText);
    m_model->setColumnCount(columnCount);

    for (int i = 0; i < columnCount; i++) {
        m_treeView->setColumnWidth(i, columnWidth.at(i));
    }
}

void CountCodeWidget::initBottomWidget()
{
    m_bottomWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout;
    m_bottomWidget->setLayout(layout);

    QLabel *fileLabel = new QLabel("文件数",this);
    m_fileCountLabel = new StyleLabel(this);
    m_fileCountLabel->setMinimumWidth(80);
    QLabel *codeLabel = new QLabel("代码行数",this);
    m_codeCountLabel = new StyleLabel(this);
    m_codeCountLabel->setMinimumWidth(80);
    m_labPercentCode = new QLabel("0%",this);
    m_labPercentCode->setMinimumWidth(60);
    m_labPercentCode->setFrameShadow(QFrame::Sunken);
    m_labPercentCode->setFrameShape(QFrame::Box);
    m_labPercentCode->setAlignment(Qt::AlignCenter);
    m_labPercentNote = new QLabel("0%",this);
    m_labPercentNote->setMinimumWidth(60);
    m_labPercentNote->setFrameShadow(QFrame::Sunken);
    m_labPercentNote->setFrameShape(QFrame::Box);
    m_labPercentNote->setAlignment(Qt::AlignCenter);
    m_labPercentBlank = new QLabel("0%",this);
    m_labPercentBlank->setMinimumWidth(60);
    m_labPercentBlank->setFrameShadow(QFrame::Sunken);
    m_labPercentBlank->setFrameShape(QFrame::Box);
    m_labPercentBlank->setAlignment(Qt::AlignCenter);
    QLabel *sizeLabel = new QLabel("字节数",this);
    m_sizeCountLabel = new StyleLabel(this);
    m_sizeCountLabel->setMinimumWidth(80);
    QLabel *rowsLabel = new QLabel("总行数",this);
    m_rowsCountlabel = new StyleLabel(this);
    m_rowsCountlabel->setMinimumWidth(80);
    QLabel *noteLabel = new QLabel("注释行数",this);
    m_noteCountLabel = new StyleLabel(this);
    m_noteCountLabel->setMinimumWidth(80);
    QLabel *blankLabel = new QLabel("空白行数",this);
    m_blankCountlabel = new StyleLabel(this);
    m_blankCountlabel->setMinimumWidth(80);

    QLabel *label = new QLabel("文件",this);
    QLabel *dirLabel = new QLabel("目录",this);
    QLabel *filterLabel = new QLabel("过滤", this);

    m_edit = new QLineEdit(this);
    m_edit->setReadOnly(true);
    m_dirEdit = new QLineEdit(this);
    m_dirEdit->setReadOnly(true);
    QLineEdit *filterEdit = new QLineEdit(this);
    filterEdit->setText(fileFilter);
    filterEdit->setReadOnly(true);

    DSuggestButton *openFileBtn = new DSuggestButton("打开文件", this);
    DSuggestButton *openDirBtn = new DSuggestButton("打开目录", this);
    DSuggestButton *clearBtn = new DSuggestButton("清除数据", this);

    layout->addWidget(fileLabel, 0 , 0);
    layout->addWidget(m_fileCountLabel, 0 , 1);
    layout->addWidget(codeLabel, 0 , 2);
    layout->addWidget(m_codeCountLabel, 0 , 3);
    layout->addWidget(m_labPercentCode, 0 , 4);
    layout->addWidget(label, 0 , 5);
    layout->addWidget(m_edit, 0 , 6);
    layout->addWidget(openFileBtn, 0 , 7);
    layout->addWidget(sizeLabel, 1 , 0);
    layout->addWidget(m_sizeCountLabel, 1 , 1);
    layout->addWidget(noteLabel, 1 , 2);
    layout->addWidget(m_noteCountLabel, 1 , 3);
    layout->addWidget(m_labPercentNote, 1 , 4);
    layout->addWidget(dirLabel, 1 , 5);
    layout->addWidget(m_dirEdit, 1 , 6);
    layout->addWidget(openDirBtn, 1 , 7);
    layout->addWidget(rowsLabel, 2 , 0);
    layout->addWidget(m_rowsCountlabel, 2 , 1);
    layout->addWidget(blankLabel, 2 , 2);
    layout->addWidget(m_blankCountlabel, 2 , 3);
    layout->addWidget(m_labPercentBlank, 2 , 4);
    layout->addWidget(filterLabel, 2 , 5);
    layout->addWidget(filterEdit, 2 , 6);
    layout->addWidget(clearBtn, 2 , 7);


    connect(openFileBtn, &QPushButton::clicked, this, &CountCodeWidget::onOpenFile);
    connect(openDirBtn, &QPushButton::clicked, this, &CountCodeWidget::onOpenPath);
    connect(clearBtn, &QPushButton::clicked, this, &CountCodeWidget::onClearData);
}

QIcon CountCodeWidget::getIcon(QString filename)
{
    QFileInfo file_info(filename);
    QFileIconProvider file_icon;
    QIcon icon = file_icon.icon(file_info);
    return icon;
}

void CountCodeWidget::deleteAllData()
{
    if (m_model->rowCount() <= 0)
        return;

    for (int i = m_model->rowCount() - 1; i >= 0; i--) {
        m_model->removeRow(i);
    }
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

void CountCodeWidget::setLabelStyle()
{
    m_fileCountLabel->setTextColor(QColor("#17A086"));
    m_codeCountLabel->setTextColor(QColor("#CA5AA6"));
    m_sizeCountLabel->setTextColor(QColor("#CD1B19"));
    m_rowsCountlabel->setTextColor(QColor("#22A3A9"));
    m_noteCountLabel->setTextColor(QColor("#D64D54"));
    m_blankCountlabel->setTextColor(QColor("#A279C5"));

    QFont font;
    font.setBold(true);

    m_fileCountLabel->setFont(font);
    m_codeCountLabel->setFont(font);
    m_sizeCountLabel->setFont(font);
    m_rowsCountlabel->setFont(font);
    m_noteCountLabel->setFont(font);
    m_blankCountlabel->setFont(font);
}

bool CountCodeWidget::checkFile(const QString &fileName)
{
    if (fileName.startsWith("moc_") || fileName.startsWith("ui_") || fileName.startsWith("qrc_")) {
        return false;
    }

    QFileInfo file(fileName);
    QString suffix = "*." + file.suffix();
    QStringList filters = fileFilter.split(" ");
    return filters.contains(suffix);
}

void CountCodeWidget::countCode(const QString &filePath)
{
    QDir dir(filePath);
    QFileInfoList fileInfos = dir.entryInfoList();
    foreach (QFileInfo fileInfo, fileInfos) {
        QString fileName = fileInfo.fileName();
        if (fileInfo.isFile()) {
            if (checkFile(fileName)) {
                listFile << fileInfo.filePath();
            }
        } else {
            if (fileName == "." || fileName == "..") {
                continue;
            }

            //递归找出文件
            countCode(fileInfo.absoluteFilePath());
        }
    }
}

void CountCodeWidget::countCode(const QStringList &files)
{
    int lineCode;
    int lineBlank;
    int lineNotes;
    int count = files.count();

    quint32 totalLines = 0;
    quint32 totalBytes = 0;
    quint32 totalCodes = 0;
    quint32 totalNotes = 0;
    quint32 totalBlanks = 0;

    for (int i = 0; i < count; i++) {
        QFileInfo fileInfo(files.at(i));
        countCode(fileInfo.filePath(), lineCode, lineBlank, lineNotes);
        int lineAll = lineCode + lineBlank + lineNotes;

        QStandardItem *itemName = new QStandardItem;
        itemName->setText(fileInfo.fileName());
        itemName->setIcon(getIcon(fileInfo.filePath()));

        QStandardItem *itemSuffix = new QStandardItem;
        itemSuffix->setText(fileInfo.suffix());

        QStandardItem *itemSize = new QStandardItem;
        itemSize->setText(QString::number(fileInfo.size()));

        QStandardItem *itemLine = new QStandardItem;
        itemLine->setText(QString::number(lineAll));

        QStandardItem *itemCode = new QStandardItem;
        itemCode->setText(QString::number(lineCode));

        QStandardItem *itemNote = new QStandardItem;
        itemNote->setText(QString::number(lineNotes));

        QStandardItem *itemBlank = new QStandardItem;
        itemBlank->setText(QString::number(lineBlank));

        QList<QStandardItem *> listItem;
        listItem << itemName << itemSuffix << itemSize << itemLine << itemCode << itemNote << itemBlank;

        m_model->appendRow(listItem);

        totalBytes  += fileInfo.size();
        totalLines  += lineAll;
        totalCodes  += lineCode;
        totalNotes  += lineNotes;
        totalBlanks += lineBlank;

        if (i % 100 == 0) {
            qApp->processEvents();
        }
    }

    listFile.clear();
    m_fileCountLabel->setText(QString::number(count));
    m_sizeCountLabel->setText(QString::number(totalBytes));
    m_rowsCountlabel->setText(QString::number(totalLines));
    m_codeCountLabel->setText(QString::number(totalCodes));
    m_noteCountLabel->setText(QString::number(totalNotes));
    m_blankCountlabel->setText(QString::number(totalBlanks));

    double percent = 0.0;
    percent = ((double)totalCodes / totalLines) * 100;
    m_labPercentCode->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));

    percent = ((double)totalNotes / totalLines) * 100;
    m_labPercentNote->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));

    percent = ((double)totalBlanks / totalLines) * 100;
    m_labPercentBlank->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));
}

void CountCodeWidget::countCode(const QString &fileName, int &lineCode, int &lineBlank, int &lineNotes)
{
    lineCode = lineBlank = lineNotes = 0;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly)) {
        QTextStream out(&file);
        QString line;
        bool isNote = false;
        while (!out.atEnd()) {
            line = out.readLine();
            line = line.trimmed();
            //判断当前行是否是注释
            if (line.startsWith("/*")) {
                isNote = true;
            }

            if (isNote) {
                lineNotes++;
            } else {
                if (line.startsWith("//")) {
                    lineNotes++;
                } else if (line.isEmpty()) {
                    lineBlank++;
                } else {
                    lineCode++;
                }
            }

            if (line.endsWith("*/")) {
                isNote = false;
            }
        }
    }
}

void CountCodeWidget::onOpenFile()
{
    QString filter = QString("代码文件(%1)").arg(fileFilter);
    QStringList files = QFileDialog::getOpenFileNames(this, "选择文件", "./", filter);
    if (files.size() > 0) {
        onClearData();
        m_edit->setText(getElidedText(m_edit->font(), files.join("|"), m_edit->width()));
        QtConcurrent::run(this, QOverload<const QStringList &>::of(&CountCodeWidget::countCode), files);
    }
}

void CountCodeWidget::onOpenPath()
{
    QString path = QFileDialog::getExistingDirectory(this, "选择目录", "./",  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!path.isEmpty()) {
        onClearData();
        m_dirEdit->setText(getElidedText(m_dirEdit->font(), path, m_dirEdit->width()));
        listFile.clear();
        countCode(path);
        QtConcurrent::run(this, QOverload<const QStringList &>::of(&CountCodeWidget::countCode), listFile);
    }
}

void CountCodeWidget::onClearData()
{   
    m_fileCountLabel->setText("0");
    m_sizeCountLabel->setText("0");
    m_rowsCountlabel->setText("0");
    m_codeCountLabel->setText("0");
    m_noteCountLabel->setText("0");
    m_blankCountlabel->setText("0");

    m_labPercentCode->setText("0%");
    m_labPercentNote->setText("0%");
    m_labPercentBlank->setText("0%");
    m_edit->clear();
    m_dirEdit->clear();

    deleteAllData();
}
