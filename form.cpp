#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ser=new serialPort(this);
    set=new QSettings("MyCompany", "MyApp");
    this->restoreGeometry(set->value("geometr").toByteArray());
    foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) // добавляем в форму доступные ком порты
        {
            ui->cmbcom->addItem(port.portName());
        }
    ui->BaudRateBox->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->BaudRateBox->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->BaudRateBox->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->BaudRateBox->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->BaudRateBox->setCurrentIndex(set->value("Baudrate").toInt()); //востанавливаем предыдущее значение
}
Form::~Form()
{
    delete ui;
}

void Form::closeEvent(QCloseEvent *)
{
    set->setValue("geometr",saveGeometry());
    set->setValue("Baudrate",ui->BaudRateBox->currentIndex());
    return;
}

void Form::on_pbtopen_clicked()
{

}

void Form::on_pbtupdate_clicked() //обновляем доступные порты
{
     ui->cmbcom->clear();
     foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) // добавляем в форму доступные ком порты
         {
             ui->cmbcom->addItem(port.portName());
         }

}
