#include "lab_main_form.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	LabMainForm w;
    w.showMaximized();
    return a.exec();
}
