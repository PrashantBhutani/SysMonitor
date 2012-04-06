#include "monitor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    settingTabs mainWidget;
    mainWidget.show();
    return a.exec();
}
