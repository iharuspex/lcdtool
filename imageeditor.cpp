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
    QImage img("../test_3_128x64.png");
    //img = img.scaled(128, 64);

    img = FSDithering(img);

    auto *scene = new QGraphicsScene;
    auto *item = new QGraphicsPixmapItem(QPixmap::fromImage(img));
    scene->addItem(item);
    ui->graphicsView->setScene(scene);

    QString output = "const unsigned char gImage_1in54[] = {\n";
    int elem_counter = 0;
    // 1 byte == 8 pixels!
    quint8 imgByte = 0;
    int byteFullCnt = 0;

    std::cout << "Width:  " << img.width() << std::endl
              << "Height: " << img.height() << std::endl;

    for ( int row = 0; row < img.height(); row++ ) {
        for ( int col = 0; col < img.width(); col++ ) {
            QColor clrCurrent(img.pixel(col, row));

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
    if (hsv_val <= 96 ) {
        return 0;
    } else {
        return 255;
    }
}

QImage ImageEditor::FSDithering(QImage &image) {
    QImage img(image);

    int oldpixel = 0;
    int newpixel = 0;

    for ( int row = 0; row < img.height(); row++ ) {
        for (int col = 0; col < img.width(); col++) {
            QColor clrCurrent(img.pixel(col, row));

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

            img.setPixelColor(col, row, QColor::fromHsv(0, 0, newpixel));

            if (col + 1 < img.width()) {
                img.setPixelColor(col + 1, row, QColor::fromHsv(0, 0, QColor(img.pixel(col + 1, row)).value() + (quant_error * 7/16)));
            }

            if (row + 1 < img.height() && col + 1 < img.width()) {
                img.setPixelColor(col + 1, row + 1, QColor::fromHsv(0, 0, QColor(img.pixel(col + 1, row + 1)).value() + (quant_error * 1/16)));
            }

            if (row + 1 < img.height()) {
                img.setPixelColor(col, row + 1, QColor::fromHsv(0, 0, QColor(img.pixel(col, row + 1)).value() + (quant_error * 5/16)));
            }

            if (row + 1 < img.height() && col - 1 >= 0) {
                img.setPixelColor(col - 1, row + 1, QColor::fromHsv(0, 0, QColor(img.pixel(col - 1, row + 1)).value() + (quant_error * 3/16)));
            }
        }
    }

    return img;
}

