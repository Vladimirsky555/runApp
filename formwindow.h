#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "formitem.h"

namespace Ui {
class FormWindow;
}

class FormWindow : public QWidget
{
    Q_OBJECT

    int _paceMin;
    int _paceSec;
    int count;
    float lastKm;
    bool flag;
    int res;
    int resChanged;
    int resRest;

    QPushButton *b;
    QPushButton *c;

    QList<FormItem*> items;

public:
    explicit FormWindow(int res, int _paceMin, int _paceSec, int count, float lastKm, bool flag, QWidget *parent = 0);
    ~FormWindow();

    //int resultCount();
    void clearAll();

private slots:
    void Recount();
    void Clear();
    void reDraw();

private:
    Ui::FormWindow *ui;
};



#endif // FORMWINDOW_H
