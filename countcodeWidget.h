#ifndef FRMCOUNTCODE_H
#define FRMCOUNTCODE_H

#include <QWidget>
#include <DSuggestButton>

class QLineEdit;
class TreeView;
class QStandardItemModel;
class QLabel;
class StyleLabel;

DWIDGET_USE_NAMESPACE

class CountCodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountCodeWidget(QWidget *parent = Q_NULLPTR);
    ~CountCodeWidget();

    void initBottomWidget();

private:
    QStringList listFile;

private:
    void initForm();
    bool checkFile(const QString &fileName);
    void countCode(const QString &filePath);
    void countCode(const QStringList &files);
    void countCode(const QString &fileName, int &lineCode, int &lineBlank, int &lineNotes);
    QIcon getIcon(QString filename);
    void deleteAllData();
    void setLabelStyle();
    QString getElidedText(QFont font, QString str, int MaxWidth);

private slots:
    void onOpenFile();
    void onOpenPath();
    void onClearData();

private:
    QLineEdit *m_edit = Q_NULLPTR;
    QLineEdit *m_dirEdit = Q_NULLPTR;
    QWidget *m_bottomWidget = Q_NULLPTR;
    QStandardItemModel *m_model = Q_NULLPTR;
    TreeView *m_treeView = Q_NULLPTR;

    StyleLabel *m_fileCountLabel = Q_NULLPTR;
    StyleLabel *m_codeCountLabel = Q_NULLPTR;
    StyleLabel *m_sizeCountLabel = Q_NULLPTR;
    StyleLabel *m_rowsCountlabel = Q_NULLPTR;
    StyleLabel *m_noteCountLabel = Q_NULLPTR;
    StyleLabel *m_blankCountlabel = Q_NULLPTR;

    QLabel *m_labPercentCode = Q_NULLPTR;
    QLabel *m_labPercentNote = Q_NULLPTR;
    QLabel *m_labPercentBlank = Q_NULLPTR;
};

#endif // FRMCOUNTCODE_H
