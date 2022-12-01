#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->imageEdButton, &QPushButton::clicked, this, &MainWindow::openImageEditor);
    connect(ui->fontEdButton, &QPushButton::clicked, this, &MainWindow::openFontEditor);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImageEditor() {
    imageEditor = new ImageEditor();
    imageEditor->show();
}

void MainWindow::openFontEditor() {
    fontEditor = new FontEditor();
    fontEditor->show();
}

