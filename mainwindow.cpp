#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Parkrun Tula calculator");
    ui->edtDistance->setText(QString::number(4900));
    ui->btnStrategy->setEnabled(false);

    ui->lstAll->addItem("Паркран Тула вконтакте");
    ui->lstAll->addItem("parkrun Тула Центральный парк");
    ui->lstAll->addItem("Последние результаты");
    ui->lstAll->addItem("Тульский марафон вконтакте");
    ui->lstAll->addItem("Первый тульский беговой клуб вконтакте");
    ui->lstAll->addItem("Волонтёрство");
    ui->lstAll->addItem("Пластиковые карты parkrun");
    ui->lstAll->addItem("Паркран Россия в фейсбуке");
    ui->lstAll->addItem("Помочь parkrun");
    ui->lstAll->addItem("Регистрация parkrun Россия");
    ui->lstAll->addItem("Russia Running");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::change(QString s)
{
    QString temp;

    if(s == "Паркран Тула вконтакте"){
        temp = "https://vk.com/parkruntula";
    }else if(s == "parkrun Тула Центральный парк"){
        temp = "https://www.parkrun.ru/tulacentral";
    }else if(s == "Последние результаты"){
        temp = "https://www.parkrun.ru/tulacentral/results/latestresults";
    }else if(s == "Тульский марафон вконтакте"){
        temp = "https://vk.com/tulamarathon";
    }else if(s == "Первый тульский беговой клуб вконтакте"){
        temp = "https://vk.com/tularunners";
    }else if(s == "Волонтёрство"){
        temp = "https://www.parkrun.ru/tulacentral/volunteer";
    }else if(s == "Пластиковые карты parkrun"){
        temp = "https://parkrun-id.ru";
    }else if(s == "Паркран Россия в фейсбуке"){
        temp = "https://www.facebook.com/parkrunRU";
    }else if(s == "Помочь parkrun"){
        temp = "https://www.parkrun.ru/helpparkrun";
    }else if(s == "Регистрация parkrun Россия"){
        temp = "https://www.parkrun.ru/register";
    }else if(s == "Russia Running"){
        temp = "https://russiarunning.com";
    }

    return temp;
}


void MainWindow::on_btnStart_clicked()
{
    ui->btnStrategy->setEnabled(true);
    ui->edtResHour->clear();
    ui->edtResMin->clear();
    ui->edtResSec->clear();

    this->distance = ui->edtDistance->text().toInt();
    this->paceMin = ui->edtPaceMin->text().toInt();
    this->paceSec = ui->edtPaceSec->text().toInt();

    if(paceMin >= 60 || paceSec >= 60){
        QMessageBox b;
        b.setText("Число не может быть больше 60");
        b.exec();
        return;
    }

    distance = distance/1000;
    pace = 60 * paceMin + paceSec;

    res = pace * distance;

        hour = res / 3600;
        res -= hour * 3600;
        minutes = res / 60;
        newSec = res - minutes * 60;

        if(hour >= 24){
            QMessageBox b;
            b.setText("Число не может быть больше 24");
            b.exec();
            return;
        }

        if(minutes >= 60 || newSec >= 60){
            QMessageBox b;
            b.setText("Число не может быть больше 60");
            b.exec();
            return;
        }

        ui->edtResHour->setText(QString::number(hour));
        ui->edtResMin->setText(QString::number(minutes));
        ui->edtResSec->setText(QString::number(newSec));
}

void MainWindow::on_btnStartTime_clicked()
{
    ui->edtPaceMin->clear();
    ui->edtPaceSec->clear();
    ui->btnStrategy->setEnabled(false);

    this->distance = ui->edtDistance->text().toInt();
    this->resHour = ui->edtResHour->text().toInt();
    this->resMin = ui->edtResMin->text().toInt();
    this->resSec = ui->edtResSec->text().toInt();

    if(resHour >= 24){
        QMessageBox b;
        b.setText("Число не может быть больше 24");
        b.exec();
        return;
    }

    if(resMin >= 60 || resSec >= 60){
        QMessageBox b;
        b.setText("Число не может быть больше 60");
        b.exec();
        return;
    }

    distance = distance/1000;
    res = resHour * 3600 + resMin * 60 + resSec;
    pace = res/distance;

    minutes = pace / 60;
    newSec = pace - minutes * 60;

    if(minutes >= 60 || newSec >= 60){
        QMessageBox b;
        b.setText("Число не может быть больше 60");
        b.exec();
        return;
    }

    ui->edtPaceMin->setText(QString::number(minutes));
    ui->edtPaceSec->setText(QString::number(newSec));
}

void MainWindow::on_btnClear_clicked()
{
    ui->edtResHour->clear();
    ui->edtResMin->clear();
    ui->edtResSec->clear();
    ui->edtPaceMin->clear();
    ui->edtPaceSec->clear();
}


void MainWindow::on_lstAll_clicked()
{
    int id = ui->lstAll->currentRow();
    if (id == -1) return;
    QDesktopServices::openUrl(QUrl(change(ui->lstAll->item(id)->text())));
}


void MainWindow::on_btnStrategy_clicked()
{
    distance = ui->edtDistance->text().toInt();
    distanceInt = distance / 1000;

    if(distance/1000 - distanceInt > 0){
        flag = true;
    } else {
        flag = false;
    }

    //Вычисляем результат
    this->resHour = ui->edtResHour->text().toInt();
    this->resMin = ui->edtResMin->text().toInt();
    this->resSec = ui->edtResSec->text().toInt();
    res = resHour * 3600 + resMin * 60 + resSec;

    float tmp = distance - distanceInt * 1000;
    tmp = tmp/1000;

    if(distanceInt < 25){
    fw = new FormWindow(res, paceMin, paceSec, distanceInt, tmp, flag);
    fw->show();
    } else {
        QMessageBox b;
        b.setText("Больше 24 километров стратегия не работает");
        b.exec();
        return;
    }

}
