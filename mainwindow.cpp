#include "mainwindow.h"
#include <QString>
#include <QBitmap>
#include <QPainter>
#include <QImage>
#include <QDebug>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainLayout = new QVBoxLayout();
    goButton = new QPushButton("Go");
    label = new QLabel();
    font = new QFont("Times New Roman");
    fontDatabase = new QFontDatabase();
    fontComboBox = new QComboBox();

    fontComboBox->addItems(fontDatabase->families());

    mainLayout->addWidget(fontComboBox);
    mainLayout->addWidget(goButton);
    mainLayout->addWidget(label);

    auto *mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);

    //connect(goButton, SIGNAL(pressed()), this, SLOT(go_slot()));
    //connect(fontComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(go_slot(int)));

    QImage img("../test.png");
    img.convertTo(QImage::Format_ARGB32);
    img = img.scaled(200, 200);

    QVector<QRgb> v = img.colorTable();

    QRgb rgb = img.pixel(0, 0);
    QColor rgbColor(rgb);
    std::cout << "Red: " << rgbColor.red() << std::endl
            << "Green: " << rgbColor.green() << std::endl
            << "Blue: " << rgbColor.blue() << std::endl;


    for ( int col = 0; col < img.width() - 1; ++col ) {
        for ( int row = 0; row < img.height() - 1; ++row ) {

            QColor clrCurrent(img.pixel(row, col));

            if (clrCurrent.value() == 0xFF) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }

        }
        std::cout << std::endl;
    }

    QPainter painter(this);
    painter.drawImage(0, 0, img);
    label->setPixmap(QPixmap::fromImage(img));
    label->show();
}

MainWindow::~MainWindow() = default;


void MainWindow::go_slot(int index)
{
    font->setFamily(fontComboBox->currentText());
    QFontMetrics fontMetrics(*font);

    QBitmap newBitmap;

    QImage image(1920, 1024, QImage::Format_RGB32);
    QPainter p;
    if (!p.begin(&image)) return;

    p.fillRect(QRect(0, 0, 1920, 1024), Qt::white);
    p.setPen(QPen(Qt::black));
    p.setFont(QFont(fontComboBox->currentText(), 25, QFont::Bold));
    p.drawText(image.rect(), Qt::AlignCenter, QString(CHAR_SET_RU));
    p.end();

    label->setPixmap(QPixmap::fromImage(image));
    label->show();
}
