#ifndef TEMP_H
#define TEMP_H

#include <QWidget>

namespace Ui {
class Temp;
}

class Temp : public QWidget
{
    Q_OBJECT

    int _temp;

public:
    explicit Temp(int temp, QWidget *parent = 0);
    ~Temp();

private:
    Ui::Temp *ui;
};

#endif // TEMP_H
