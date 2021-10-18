#include "management_system.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    management_system w;
    w.show();
    return a.exec();
}
