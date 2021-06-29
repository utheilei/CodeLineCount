#ifndef COUNTCODEWIDGET_H
#define COUNTCODEWIDGET_H

#include <QWidget>

class TreeView;
class CountCodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountCodeWidget(QWidget *parent = Q_NULLPTR);
    ~CountCodeWidget();

    void initUi();

    virtual void initBottomWidget();

    virtual void deleteAllData() = 0;

    virtual void setLabelStyle();

    virtual void onClearData();

    virtual void initForm();

protected:
    QIcon getIcon(QString filename);

    QString getElidedText(QFont font, QString str, int MaxWidth);

protected:
    TreeView *m_treeView = Q_NULLPTR;
    QWidget *m_bottomWidget = Q_NULLPTR;
};

#endif // COUNTCODEWIDGET_H
