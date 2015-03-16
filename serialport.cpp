#include "serialport.h"
#include <QDebug>

serialPort::serialPort(QObject *parent) : QObject(parent)
{
    thisPort=new QSerialPort(this);
    seting =new QSettings("MyCompany", "MyApp",this);
    name=seting->value("Com port","/dev/ttyUSB0").toString();
    baudRate =seting->value("baudRate",QSerialPort::Baud115200).toInt();
}

serialPort::~serialPort()
{
    seting->setValue("Com port",name);
    seting->setValue("baudrate",baudRate);
    emit finished_Port();
}

void serialPort :: process_Port()
{
    qDebug() << "process_Port";
    connect(thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
}

void serialPort :: ConnectPort()
{//
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
        emit openPort();
    }
    }
   else
   {
        thisPort->close();
        emit closePort();
        error_(thisPort->errorString().toLocal8Bit());
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
    emit closePort();
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

void serialPort::changePort(QString namecom)
{
    if(thisPort->isOpen())
    {
        thisPort->close();
        emit closePort();
        qDebug() << "Порт закрыт " << name;
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
         qDebug() << "Порт открыт изменена скорость";
    }
    qDebug() << "изменена скорость" << baudRate;
}
