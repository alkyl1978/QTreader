#include "serialport.h"
#include <QDebug>

serialPort::serialPort(QObject *parent) : QObject(parent)
{
    thisPort=new QSerialPort(this);
    seting =new QSettings("MyCompany", "MyApp",this);
    name=seting->value("Com port","/dev/ttyUSB0").toString();
    baudRate =seting->value("baudRate",QSerialPort::Baud115200).toInt();
    portinfo=new QSerialPortInfo(name);
    qDebug() << "конструктор" << name;
}

serialPort::~serialPort()
{
    seting->setValue("Com port",name);
    seting->setValue("baudrate",baudRate);
    qDebug() << "деструктор";
    emit finished_Port();
}

void serialPort :: process_Port()
{
    qDebug() << "process_Port";
connect(thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
connect(thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
connect(thisPort,SIGNAL(aboutToClose()),this,SLOT(toClose()));
}

void serialPort :: ConnectPort()
{//
    portinfo->portName()=name;
    if((portinfo->isValid()))
    {
        emit isvalid();
        return;
    }
    thisPort->setPortName(name);
    if (thisPort->open(QIODevice::ReadWrite))
    {
        if (thisPort->setBaudRate(baudRate)
        && thisPort->setDataBits(QSerialPort::Data8)
        && thisPort->setParity(QSerialPort::NoParity)
        && thisPort->setStopBits(QSerialPort::OneStop)
        && thisPort->setFlowControl(QSerialPort::NoFlowControl))
    {
    if (thisPort->isOpen())
    {
        error_((name+ " >> Открыт!\r").toLocal8Bit());
        qDebug() << "Порт открыт" << name << "скорость " << baudRate ;
    }
    }
   else
   {
        thisPort->close();
        error_(thisPort->errorString().toLocal8Bit());
        emit isvalid();
    }
    }
}


void serialPort::handleError(QSerialPort::SerialPortError error)//
{
if ( (thisPort->isOpen()) && (error == QSerialPort::ResourceError)) {
error_(thisPort->errorString().toLocal8Bit());
}
}//

void serialPort::DisconnectPort()
{
if(thisPort->isOpen())
{
    thisPort->close();
    error_(name.toLocal8Bit() + " >> Закрыт!\r");
    qDebug() << "Порт закрыт" << name;
}
}

void serialPort :: WriteToPort(QByteArray data)
{
if(thisPort->isOpen())
    {
        thisPort->write(data);
    }
}

void serialPort :: ReadInPort()
{
    QByteArray data;
    thisPort->waitForReadyRead(50);
    data.append(thisPort->readAll());
    emit outPort(data);
}

void serialPort::toClose()
{
    emit isvalid();
}

void serialPort::changePort(QString namecom)
{
    if(thisPort->isOpen())
    {
        thisPort->close();
    }
    name=namecom;
    qDebug() << "Порт изменен" << name;
}

void serialPort::changebaud(QString baund)
{
    baudRate=baund.toInt();
    if(thisPort->isOpen())
    {
        thisPort->setBaudRate(baudRate);
    }
    qDebug() << "изменена скорость" << baudRate;
}
