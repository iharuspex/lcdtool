#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QImage>
#include <QString>
#include <QFile>

#include <iostream>

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

    connect(ui->actionConvert, &QAction::triggered, this, &ImageEditor::onConvertToArray);
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

void ImageEditor::onConvertToArray() {
    QImage img("../test.png");
    img = img.scaled(200, 200);

    img = FSDithering(img);

    auto *scene = new QGraphicsScene;
    auto *item = new QGraphicsPixmapItem(QPixmap::fromImage(img));
    scene->addItem(item);
    ui->graphicsView->setScene(scene);

    QRgb rgb = img.pixel(0, 0);
    QColor rgbColor(rgb);
    std::cout << "Red: " << rgbColor.red() << std::endl
              << "Green: " << rgbColor.green() << std::endl
              << "Blue: " << rgbColor.blue() << std::endl;

    QString output = "const unsigned char gImage_1in54[5000] = {\n";
    int elem_counter = 0;
    // 1 byte == 8 pixels!
    quint8 imgByte = 0;
    int byteFullCnt = 0;

    std::cout << "Width:  " << img.width() << std::endl
              << "Height: " << img.height() << std::endl;

    for ( int col = 0; col < img.width(); col++ ) {
        for ( int row = 0; row < img.height(); row++ ) {
            QColor clrCurrent(img.pixel(row, col));

            if (clrCurrent.value() != 0) {
                imgByte |= 1 << (7u - byteFullCnt);
            } else {
                imgByte |= 0 << (7u - byteFullCnt);
            }
            byteFullCnt++;

            if (byteFullCnt == 8) {
                byteFullCnt = 0;

                QString val = QString::number(imgByte, 16).toUpper();
                imgByte = 0;

                if (val.length() == 1) {
                    val = "0" + val;
                }
                output += "0x" + val + ", ";
                elem_counter++;
                if (elem_counter == 15) {
                    output += "\n";
                    elem_counter = 0;
                }
            }
        }
    }
    output += "};";

    QFile file("out.txt");
    if (!file.open(QIODevice::WriteOnly)) {
        file.close();
    } else {
        file.write(output.toUtf8());
    }
}

int get_near_color(int hsv_val) {
    int new_val = 0;

    if (hsv_val <= 96 ) {
        return 0;
    } else {
        return 255;
    }
}

QImage ImageEditor::FSDithering(QImage &image) {
    QImage img(image);
    img = img.convertToFormat(QImage::Format_Mono);

    int oldpixel = 0;
    int newpixel = 0;

    for ( int col = 0; col < img.width(); col++ ) {
        for (int row = 0; row < img.height(); row++) {
            QColor clrCurrent(img.pixel(row, col));

            oldpixel = clrCurrent.value();
            newpixel = get_near_color(oldpixel);
            int quant_error = oldpixel - newpixel;

            /* Floyd–Steinberg dithering
             *
             *        X   7
             *    3   5   1
             *
             *      (1/16)
             */

            img.setPixelColor(row, col, QColor::fromHsv(0, 0, newpixel));
            img.setPixelColor(row, col + 1, QColor::fromHsv(0, 0, QColor(img.pixel(row, col + 1)).value() + (quant_error * 7/16)));
            img.setPixelColor(row + 1, col + 1, QColor::fromHsv(0, 0, QColor(img.pixel(row + 1, col + 1)).value() + (quant_error * 1/16)));
            img.setPixelColor(row + 1, col, QColor::fromHsv(0, 0, QColor(img.pixel(row + 1, col)).value() + (quant_error * 5/16)));
            img.setPixelColor(row + 1, col - 1, QColor::fromHsv(0, 0, QColor(img.pixel(row + 1, col - 1)).value() + (quant_error * 3/16)));
        }
    }

    return img;
}

