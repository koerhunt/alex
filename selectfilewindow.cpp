#include "selectfilewindow.h"
#include "ui_selectfilewindow.h"
#include<fstream>

selectFileWindow::selectFileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selectFileWindow)
{
    ui->setupUi(this);

    //Abrimos el directorio
    //dirdata = opendir("/home/shikami");

    //Mientras contenga elementos en el interior
    //while ((dp = readdir(dirdata)) != NULL){
        //ui->filetree.appendChildItem();
        //dp->d_name
    //};

    //Cerramos directorio
    //closedir(dirdata);

}

selectFileWindow::~selectFileWindow()
{
    delete ui;
}
