#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ser=new serialPort(parent);
    QThread *thread_New = new QThread(parent);//Создаем поток для порта платы
    ser->moveToThread(thread_New);
    connect(thread_New, SIGNAL(started()), ser, SLOT(process_Port()));//Переназначения метода run
    connect(ser, SIGNAL(finished_Port()), thread_New, SLOT(quit()));//Переназначение метода выход
    connect(thread_New, SIGNAL(finished()), ser, SLOT(deleteLater()));//Удалить  поток
    connect(ser, SIGNAL(finished_Port()), thread_New, SLOT(deleteLater()));//Удалить поток
    connect(ui->BtnConnect, SIGNAL(clicked()),ser,SLOT(ConnectPort()));
    connect(ui->BtnDisconect, SIGNAL(clicked()),ser,SLOT(DisconnectPort()));
    connect(ui->cmbcom,SIGNAL(currentIndexChanged(QString)),ser,SLOT(changePort(QString)));
    connect(ui->BaudRateBox, SIGNAL(currentIndexChanged(QString)) ,ser, SLOT(changebaud(QString)));
    connect(ser,SIGNAL(closePort()),this,SLOT(closeport()));
    connect(ser,SIGNAL(openPort()),this,SLOT(openport()));
    connect(ui->pbtupdate,SIGNAL(clicked()),this,SLOT(on_pbtupdate_clicked()));
    connect(this,SIGNAL(writeData(QByteArray)),ser,SLOT(WriteToPort(QByteArray)));
    connect(ser, SIGNAL(outPort(QByteArray)), this, SLOT(Print(QByteArray))); // прием данных
    connect(ser, SIGNAL(error_(QString)), ui->label, SLOT(setText(QString))); //Лог ошибок
    thread_New->start();
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

void Form::timerEvent(QTimerEvent *)
{
    emit writeData(arr_out);
}

void Form::on_pbtupdate_clicked() //обновляем доступные порты
{
     ui->cmbcom->clear();
     foreach( const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) // добавляем в форму доступные ком порты
         {
             ui->cmbcom->addItem(port.portName());
         }
     ui->BtnConnect->setEnabled(true);
}

void Form::Print(QByteArray data)
{
    qDebug() <<data.toHex();
}

void Form::closeport()
{
    ui->BtnDisconect->setEnabled(false);
    ui->BtnConnect->setEnabled(true);
    killTimer(timer);
}

void Form::openport()
{
    ui->BtnDisconect->setEnabled(true);
    ui->BtnConnect->setEnabled(false);
    timer=startTimer(1000);
}


