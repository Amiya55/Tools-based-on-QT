#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Lottery_Main_Window window;
    // window.build_window();

    Application_Window window;
    window.build_window();

    return application.exec();
}

