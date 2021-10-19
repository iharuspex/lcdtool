#include <QFileDialog>
#include <QGraphicsPixmapItem>

#include "imageeditor.h"
#include "ui_imageeditor.h"

ImageEditor::ImageEditor(QWidget *parent) :
        QWidget(parent), ui(new Ui::ImageEditor) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &ImageEditor::onLoadImage);
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

