#include "viewer_app.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewerApp w;
    w.show();

    return a.exec();
}