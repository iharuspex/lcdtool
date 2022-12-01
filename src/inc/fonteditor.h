#ifndef FONTEDITOR_H
#define FONTEDITOR_H

#include <QMainWindow>

namespace Ui {
class FontEditor;
}

class FontEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FontEditor(QWidget *parent = nullptr);
    ~FontEditor();

private:
    Ui::FontEditor *ui;
};

#endif // FONTEDITOR_H
