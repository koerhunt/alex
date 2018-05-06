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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   void openFile();


private slots:
   void on_pushButton_clicked();

   void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    selectFileWindow *sfileWindow;
};

#endif // MAINWINDOW_H
