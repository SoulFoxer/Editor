#include "../includes/mainwindow.h"  // Include your custom MainWindow class header
#include "ui_mainwindow.h"           // Include the generated UI header file

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // Set up the UI from the .ui file
}

MainWindow::~MainWindow() {
    delete ui;
}