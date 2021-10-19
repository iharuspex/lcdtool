#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    imageEditor = new ImageEditor();

    connect(ui->imageEdButton, &QPushButton::clicked, this, &MainWindow::openImageEditor);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImageEditor() {
    imageEditor->show();
}

