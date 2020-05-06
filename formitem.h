#ifndef FORMITEM_H
#define FORMITEM_H

#include <QWidget>

namespace Ui {
class FormItem;
}

class FormItem : public QWidget
{
    Q_OBJECT

    int res;
    int _paceMin;
    int _paceSec;
    float id;
    bool changedMin;
    bool changedSec;

public:
    explicit FormItem(int _paceMin, int _paceSec, float id, QWidget *parent = 0);
    ~FormItem();

    int getPaceMin();
    int getPaceRealMin();
    void setPaceMin(int);
    void setPaceItemsMin(int);

    int getPaceSec();
    int getPaceRealSec();
    void setPaceSec(int);
    int setPaceItemsSec(int);

    float getId();
    void setId(float);

    bool getChangedMin();
    void setChangedMin(bool);

    bool getChangedSec();
    void setChangedSec(bool);

private slots:
    void on_paceMin_textChanged(const QString &arg1);
    void on_paceSec_textChanged(const QString &arg1);

private:
    Ui::FormItem *ui;
};

#endif // FORMITEM_H
