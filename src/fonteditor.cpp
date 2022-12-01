#include "fonteditor.h"
#include "ui_fonteditor.h"

FontEditor::FontEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FontEditor)
{
    ui->setupUi(this);
}

FontEditor::~FontEditor()
{
    delete ui;
}
