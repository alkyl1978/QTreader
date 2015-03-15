#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    QList<QSerialPortInfo> com_ports = QSerialPortInfo::availablePorts();
    QList<qint32> baud = QSerialPortInfo::standardBaudRates();
    QSerialPortInfo port;

    ui->setupUi(this);
    ser=new serialPort(this);
    set=new QSettings("MyCompany", "MyApp");
    this->restoreGeometry(set->value("geometr").toByteArray());

    foreach(port, com_ports)
        {
            ui->cmbcom->addItem(port.portName());
        }
}
Form::~Form()
{
    delete ui;
}

void Form::closeEvent(QCloseEvent *)
{
    set->setValue("geometr",saveGeometry());
    return;
}
