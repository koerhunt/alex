#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "selectfilewindow.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
   void openFile();
   void toggled();

private slots:
   void on_pushButton_clicked();
   void on_pushButton_2_clicked();
   void on_pushButton_3_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    selectFileWindow *sfileWindow;
    void dameToken();
    int relacionaAlex(int);
    void CargarArchivoAlEditor();
    void Init();
    void AnalizaPaso();
    void guardarArchivo();
};

#endif // MAINWINDOW_H
