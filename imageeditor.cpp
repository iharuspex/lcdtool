#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

#include "imageeditor.h"
#include "ui_imageeditor.h"

ImageEditor::ImageEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::ImageEditor) {
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, this, &ImageEditor::onLoadImage);
    connect(ui->actionAbout, &QAction::triggered, []() {
        QMessageBox::about(nullptr, "About", "LCD Tool image editor\n"
                                             "Version: 0.0.1a");
    });
    connect(ui->actionAbout_Qt, &QAction::triggered, []() {
        QMessageBox::aboutQt(nullptr, "About Qt");
    });
}

ImageEditor::~ImageEditor() {
    delete ui;
}

void ImageEditor::onLoadImage() {
    QString imagePath = QFileDialog::getOpenFileName(this, "Open image file", QString(), tr("Image files (*.png, *.jpg)"));

    // Test!
    auto *scene = new QGraphicsScene;
    auto *item = new QGraphicsPixmapItem(QPixmap(imagePath));
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}

