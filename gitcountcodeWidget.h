#ifndef GITCOUNTCODEWIDGET_H
#define GITCOUNTCODEWIDGET_H

#include "countcodeWidget.h"

#include <DSuggestButton>

#include <QFileInfo>

class QLineEdit;
class QStandardItemModel;
class StyleLabel;
class QProcess;

DWIDGET_USE_NAMESPACE

class GitCountCodeWidget : public CountCodeWidget
{
    Q_OBJECT

public:
    explicit GitCountCodeWidget(QWidget *parent = Q_NULLPTR);
    ~GitCountCodeWidget() Q_DECL_OVERRIDE;

    void initBottomWidget() Q_DECL_OVERRIDE;

private:
    void initForm() Q_DECL_OVERRIDE;
    void deleteAllData() Q_DECL_OVERRIDE;
    void setLabelStyle() Q_DECL_OVERRIDE;
    void onClearData() Q_DECL_OVERRIDE;

    void parseFile();
    void addItem(QFileInfo info, int newLine, int deleteLine);

private slots:
    void onCountCode();
    void onOpenPath();

private:
    QLineEdit *m_edit = Q_NULLPTR;
    QLineEdit *m_dirEdit = Q_NULLPTR;
    QLineEdit *m_timeEdit = Q_NULLPTR;
    QStandardItemModel *m_model = Q_NULLPTR;

    StyleLabel *m_fileCountLabel = Q_NULLPTR;
    StyleLabel *m_codeCountLabel = Q_NULLPTR;
    StyleLabel *m_sizeCountLabel = Q_NULLPTR;
};

#endif // GITCOUNTCODEWIDGET_H
