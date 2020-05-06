#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formwindow.h"
#include "temp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    float distance;
    int distanceInt;

    int res;
    int resHour;
    int resMin;
    int resSec;

    int pace;
    int paceMin;
    int paceSec;

    int minutes;
    int hour;
    int newSec;

    bool flag;

    FormWindow *fw;
    Temp *t;



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_btnStart_clicked();
    void on_btnStartTime_clicked();
    void on_btnClear_clicked();
    void on_lstAll_clicked();
    QString change(QString s);

    void on_btnStrategy_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
