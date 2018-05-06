#ifndef SELECTFILEWINDOW_H
#define SELECTFILEWINDOW_H

#include <QMainWindow>
#include <dirent.h>

namespace Ui {
class selectFileWindow;
}

class selectFileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit selectFileWindow(QWidget *parent = 0);
    ~selectFileWindow();
    void threeFull();
private:
    Ui::selectFileWindow *ui;
    dirent *dp; //dirItem
    DIR *dirdata; //dirData
};

#endif // SELECTFILEWINDOW_H
