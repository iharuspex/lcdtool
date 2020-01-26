#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

public slots:
    void go_slot();

private:
    QVBoxLayout *mainLayout;
    QFont *font;
    QFontDatabase *fontDatabase;
    QComboBox *fontComboBox;
    QPushButton *goButton;
    QLabel *label;
};

#endif // MAINWINDOW_H
