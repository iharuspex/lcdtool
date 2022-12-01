//
// Created by haruspex on 10/19/21.
//

#ifndef LCDTOOL_IMAGEEDITOR_H
#define LCDTOOL_IMAGEEDITOR_H

#include <QMainWindow>

#include "croptoolitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageEditor; }
QT_END_NAMESPACE

class ImageEditor : public QMainWindow {
Q_OBJECT

public:
    explicit ImageEditor(QWidget *parent = nullptr);

    ~ImageEditor() override;

private slots:
    void onLoadImage();

    void onConvertToArray();

    QImage FSDithering(QImage &);

private:
    Ui::ImageEditor *ui;

    QString imagePath;

    CropToolItem *cropToolItem;
};


#endif //LCDTOOL_IMAGEEDITOR_H
