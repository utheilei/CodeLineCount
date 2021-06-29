#ifndef LOCALCOUNTCODEWIDGET_H
#define LOCALCOUNTCODEWIDGET_H

#include "countcodeWidget.h"

#include <DSuggestButton>

class QLineEdit;
class QStandardItemModel;
class QLabel;
class StyleLabel;

DWIDGET_USE_NAMESPACE

class LocalCountCodeWidget : public CountCodeWidget
{
    Q_OBJECT

public:
    explicit LocalCountCodeWidget(QWidget *parent = Q_NULLPTR);
    ~LocalCountCodeWidget() Q_DECL_OVERRIDE;

    void initBottomWidget() Q_DECL_OVERRIDE;

private:
    void initForm() Q_DECL_OVERRIDE;
    void deleteAllData() Q_DECL_OVERRIDE;
    void setLabelStyle() Q_DECL_OVERRIDE;

    bool checkFile(const QString &fileName);
    void countCode(const QString &filePath);
    void countCode(const QStringList &files);
    void countCode(const QString &fileName, int &lineCode, int &lineBlank, int &lineNotes);

private slots:
    void onOpenFile();
    void onOpenPath();
    void onClearData() Q_DECL_OVERRIDE;

private:
    QStringList listFile;

    QLineEdit *m_edit = Q_NULLPTR;
    QLineEdit *m_dirEdit = Q_NULLPTR;
    QStandardItemModel *m_model = Q_NULLPTR;

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

#endif // LOCALCOUNTCODEWIDGET_H
