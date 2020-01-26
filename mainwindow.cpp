#include "mainwindow.h"
#include <QString>
#include <QBitmap>
#include <QPainter>
#include <QImage>
#include <QDebug>

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

    connect(goButton, SIGNAL(pressed()), this, SLOT(go_slot()));
}

MainWindow::~MainWindow() = default;


void MainWindow::go_slot()
{
    font->setFamily(fontComboBox->currentText());
    QFontMetrics fontMetrics(*font);

    QString str = "Приветик";

    QBitmap newBitmap;

    QImage image(500, 500, QImage::Format_RGB32);
    QPainter p;
    if (!p.begin(&image)) return;

    p.fillRect(QRect(0, 0, 500, 500), Qt::white);
    p.setPen(QPen(Qt::black));
    p.setFont(QFont(fontComboBox->currentText(), 25, QFont::Bold));
    p.drawText(image.rect(), Qt::AlignCenter, str);
    p.end();

    label->setPixmap(QPixmap::fromImage(image));
    label->show();
}
