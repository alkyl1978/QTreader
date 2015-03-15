#include "serialport.h"
#include <QDebug>

serialPort::serialPort(QObject *parent) : QObject(parent)
{
    thisPort=new QSerialPort(this);
    seting =new QSettings("MyCompany", "MyApp");
    name=seting->value("Com port","/dev/ttyUSB0").toString();
    baudRate =seting->value("baudRate",QSerialPort::Baud115200).toInt();
    portinfo=new QSerialPortInfo(name);
    if(!(portinfo->isValid())) emit isvalid();
}

serialPort::~serialPort()
{
    seting->setValue("Com port",name);
    seting->setValue("baudrate",baudRate);
    emit finished_Port();
}

void serialPort :: process_Port()
{
connect(thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
connect(thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
connect(thisPort,SIGNAL(aboutToClose()),this,SLOT(toClose()));
}

void serialPort :: Write_Settings_Port(QString n, int baud)
{
name = n;
baudRate = baud;
seting->setValue("Com port",name);
seting->setValue("baudrate",baud);
}

void serialPort :: ConnectPort(QString n)
{//
    name=n;
    portinfo->portName()=name;
    if(!(portinfo->isValid()))
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
