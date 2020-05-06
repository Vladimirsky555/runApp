#include "formitem.h"
#include "ui_formitem.h"

#include <QMessageBox>

FormItem::FormItem(int _paceMin, int _paceSec, float id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormItem)
{
    ui->setupUi(this);

    this->_paceMin = _paceMin;
    this->_paceSec = _paceSec;
    this->id = id;

    this->changedMin = false;
    this->changedSec = false;

    ui->label->setText(QString::number(this->id));
    ui->paceMin->setText(QString::number(this->_paceMin));
    ui->paceSec->setText(QString::number(this->_paceSec));
}

FormItem::~FormItem()
{
    delete ui;
}

int FormItem::getPaceMin()
{
    return this->_paceMin;
}

int FormItem::getPaceRealMin()
{
    return ui->paceMin->text().toInt();
}

void FormItem::setPaceMin(int value)
{
    _paceMin = value;
    ui->paceMin->setText(QString::number(_paceMin));
}

void FormItem::setPaceItemsMin(int value)
{
    _paceMin = value;
}

int FormItem::getPaceSec()
{
    return this->_paceSec;
}

int FormItem::getPaceRealSec()
{
    return ui->paceSec->text().toInt();
}

void FormItem::setPaceSec(int value)
{
    _paceSec = value;
    ui->paceSec->setText(QString::number(_paceSec));
}

int FormItem::setPaceItemsSec(int value)
{
    _paceSec = value;
}

float FormItem::getId()
{
    return this->id;
}

void FormItem::setId(float id)
{
    this->id = id;
}

bool FormItem::getChangedMin()
{
    return this->changedMin;
}

void FormItem::setChangedMin(bool changed)
{
    this->changedMin = changed;
}

bool FormItem::getChangedSec()
{
    return this->changedSec;
}

void FormItem::setChangedSec(bool changed)
{
    this->changedSec = changed;
}

void FormItem::on_paceMin_textChanged(const QString &arg1)
{
    this->changedMin = true;
    this->changedSec = true;
}

void FormItem::on_paceSec_textChanged(const QString &arg1)
{
    this->changedMin = true;
    this->changedSec = true;
}
