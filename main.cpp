#include "widgetmain.h"
#include <QApplication>

// I need to add a button and stretch the histogram

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetMain w;
    w.showMaximized();

    return a.exec();
}
