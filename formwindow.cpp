#include "formwindow.h"
#include "ui_formwindow.h"
#include <QDebug>
#include <QMessageBox>

FormWindow::FormWindow(int res, int _paceMin, int _paceSec, int count, float lastKm, bool flag, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWindow)
{
    ui->setupUi(this);

    setWindowTitle("Стратегия " + QString::number(count + 1) + " км");

    this->res = res;
    this->_paceMin = _paceMin;
    this->_paceSec = _paceSec;
    this->lastKm = lastKm;
    this->count = count;
    this->flag = flag;

    FormItem *t = new FormItem(1, 1, 1);
    if(count <= 12){
        this->setGeometry(QRect(Qt::AlignCenter, Qt::AlignCenter,
                                t->width() + 20,
                                (count + 1)* t->height() + 40));
    } else if(count > 12){
        this->setGeometry(QRect(Qt::AlignCenter, Qt::AlignCenter,
                                (t->width() + 20) * 2,
                                12 * t->height() + 40));
    }

    reDraw();
}

FormWindow::~FormWindow()
{
    delete ui;
}

void FormWindow::clearAll()
{
    this->res = 0;
    this->_paceMin = 0;
    this->_paceSec = 0;
    this->lastKm = 0;
    this->count = 0;
    this->flag = false;
    resChanged = 0;
    resRest = 0;
}


void FormWindow::Recount()
{
    if(flag){
        if(items[items.count() - 1]->getPaceMin() > 60
                || items[items.count() - 1]->getPaceSec() > 60){
            QMessageBox b;
            b.setText("Таких не берут в космонавты!");
            b.exec();
            return;
        }

        if(!items[items.count() - 1]->getChangedMin() ||
                !items[items.count() - 1]->getChangedSec()){
            QMessageBox b;
            b.setText("Последние " + QString::number(lastKm * 1000) +
                      " метров бежим быстрее, хотя бы на секунду. "
                      "Программа пересчитает темпы всех участков, при изменении последнего.");
            b.exec();
            return;
        }
    }

    //Пробегаемся по массиву, вставляем в него те значения, которые изменили
    for(int i = 0; i < items.count(); i++){
        if(items[i]->getChangedMin() || items[i]->getChangedSec()){
          FormItem *fi = new FormItem(items[i]->getPaceRealMin(),
                                      items[i]->getPaceRealSec(),
                                      i);

          if(items[i]->getPaceMin() > 60 || items[i]->getPaceSec() > 60){
              QMessageBox b;
              b.setText("Таких не берут в космонавты!");
              b.exec();
              return;
          }

          items.replace(i, fi);

          //qDebug() << i << items[i]->getPaceMin() <<
                      //items[i]->getPaceSec();
        }
    }

    //Подсчитываем количество изменённых километров
    int tmp = 0;
    for(int i = 0; i < items.count(); i++)
    {
        if(items[i]->getChangedMin() || items[i]->getChangedSec())tmp++;
    }


    //Суммируем изменённые ячейки (секунды)
    int summaMin = 0;
    int summaSec = 0;
    for(int i = 0; i < items.count(); i++){
        if(items[i]->getChangedMin() || items[i]->getChangedSec()){
        if(flag == true && i == items.count() - 1){
            summaMin += items[i]->getPaceMin() * 60 * lastKm;
            summaSec += items[i]->getPaceSec() * lastKm;
            //qDebug() << "summaMin" << summaMin;
            //qDebug() << "summaSec" << summaSec;
        } else {
            summaMin += items[i]->getPaceMin() * 60;
            summaSec += items[i]->getPaceSec();
        }
      }
    }

    //qDebug() << "res" << res;
    resChanged = summaMin + summaSec;
    //qDebug() << "resChanged" << resChanged;
    resRest = res - resChanged;//оставшееся время
    //qDebug() << "resRest" << resRest;


    int resForItem = resRest/(items.count() - tmp);//время на каждый айтем

    //qDebug() << "resForItem" << resForItem;
    //qDebug() << "tmp" << tmp;

    //Определяем значения ячеек
    int minutes = resForItem / 60;
    int newSec = resForItem - minutes * 60;

    if(minutes >= 60 || newSec >= 60){
        QMessageBox b;
        b.setText("Число не может быть больше 60");
        b.exec();
        return;
    }

    //Меняем ячейки, которые не меняли
    for(int i = 0; i < items.count(); i++)
    {
        if(!items[i]->getChangedMin() || !items[i]->getChangedSec())
        {
            items[i]->setPaceMin(minutes);
            items[i]->setPaceSec(newSec);
        }
    }

    //Обнуляем флажки
    for(int i = 0; i < items.count(); i++){
       items[i]->setChangedMin(false);
       items.at(i)->setChangedSec(false);
    }
}

void FormWindow::Clear()
{
    items.clear();
    //items = tempItems;

    for(int i = 0; i < items.count(); i++){
        delete items[i];
    }

    delete b;
    delete c;

    reDraw();
}

void FormWindow::reDraw()
{
    FormItem *t = new FormItem(1, 1, 1);
    for(int i = 0; i < this->count + 1; i++){
        if(i == count){
            if(this->flag){
            FormItem *fi = new FormItem(this->_paceMin, this->_paceSec, i+1, this);
            QRect r = fi->geometry();

            if(i <= 11){
                r.moveTop( i * r.height());
            }else{
                r.moveTop( (i-12) * r.height());
            }

            if(i <= 11){
                r.moveLeft(0);
            }else{
                r.moveLeft(r.width());
            }

            fi->setGeometry(r);
            fi->setChangedMin(false);
            fi->setChangedSec(false);
            items.append(fi);
            fi->show();
            }
        } else {
            FormItem *fi = new FormItem(this->_paceMin, this->_paceSec, i+1, this);
            QRect r = fi->geometry();

            if(i <= 11){
                r.moveTop( i * r.height());
            }else{
                r.moveTop( (i-12) * r.height());
            }

            if(i <= 11){
                r.moveLeft(0);
            }else{
                r.moveLeft(r.width());
            }

            fi->setGeometry(r);
            fi->setChangedMin(false);
            fi->setChangedSec(false);
            items.append(fi);
            fi->show();
        }
    }



    b = new QPushButton(this);
    QRect r = b->geometry();
    if(this->flag){
        if(count < 12){
            r.moveTop((count+1) * t->height());
        } else {
            r.moveTop(12 * t->height());
        }
    } else {
        if(count < 12){
            r.moveTop(count * t->height());
        }else{
            r.moveTop(12 * t->height());
        }
    }
    r.moveLeft(10);
    b->setGeometry(r);
    b->setText("Пересчитать");
    b->setFont(QFont ("MS Shell Dlg 2", 12));

    connect(b, SIGNAL(clicked(bool)),
            this, SLOT(Recount()));

    b->show();

    //Отрисовка кнопочки "Очистить"
    c = new QPushButton(this);
    r = c->geometry();
    if(this->flag){
        if(count < 12){
            r.moveTop((count+1) * t->height());
        } else {
            r.moveTop(12 * t->height());
        }
    } else {
        if(count < 12){
            r.moveTop(count * t->height());
        }else{
            r.moveTop(12 * t->height());
        }
    }
    r.moveLeft(120);
    c->setGeometry(r);
    c->setText("Очистить");
    //с->setFont(QFont ("MS Shell Dlg 2", 12));

    connect(c, SIGNAL(clicked(bool)),
            this, SLOT(Clear()));

    c->show();
}
