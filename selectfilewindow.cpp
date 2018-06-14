#include "selectfilewindow.h"
#include "ui_selectfilewindow.h"
#include<fstream>

selectFileWindow::selectFileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selectFileWindow)
{
    ui->setupUi(this);

}

selectFileWindow::~selectFileWindow()
{
    delete ui;
}
