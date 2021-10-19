//
// Created by haruspex on 10/19/21.
//

#ifndef LCDTOOL_MAINWINDOW_H
#define LCDTOOL_MAINWINDOW_H

#include <QMainWindow>

#include "imageeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void openImageEditor();

private:
    Ui::MainWindow *ui;

    ImageEditor *imageEditor;
};


#endif //LCDTOOL_MAINWINDOW_H
