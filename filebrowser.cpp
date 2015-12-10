#include "filebrowser.h"
#include "ui_filebrowser.h"

fileBrowser::fileBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileBrowser)
{
    ui->setupUi(this);
}

fileBrowser::~fileBrowser()
{
    delete ui;
}
