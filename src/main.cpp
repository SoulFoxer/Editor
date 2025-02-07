#include <QApplication>
#include "../includes/mainwindow.h"  // Include the MainWindow class

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // Create and show the MainWindow
    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}