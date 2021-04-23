#include "mainwindow.h"

#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.loadTranslator();
    a.setOrganizationName("deepin");
    a.setApplicationName("code line count");
    a.setApplicationVersion("1.0.0");
    a.setProductIcon(QIcon::fromTheme("code_count"));
    a.setProductName("CodeLine Count Tool");
    a.setApplicationDescription("This is a code line count tool.");

    MainWindow w;
    w.setMinimumSize(900, 640);
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
