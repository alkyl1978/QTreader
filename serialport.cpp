#include "serialport.h"
#include <qdebug.h>

serialPort::serialPort(QObject *parent) : QObject(parent)
{

}

serialPort::~serialPort()
{
     emit finished_Port();
}

void serialPort :: process_Port(){
connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
}

void serialPort :: Write_Settings_Port(QString name, int baudrate,int DataBits,
int Parity,int StopBits, int FlowControl){
SettingsPort.name = name;
SettingsPort.baudRate = (QSerialPort::BaudRate) baudrate;
SettingsPort.dataBits = (QSerialPort::DataBits) DataBits;
SettingsPort.parity = (QSerialPort::Parity) Parity;
SettingsPort.stopBits = (QSerialPort::StopBits) StopBits;
SettingsPort.flowControl = (QSerialPort::FlowControl) FlowControl;
}

void serialPort :: ConnectPort(void)
{//
    thisPort.setPortName(SettingsPort.name);
    thisPort.setReadBufferSize(0);
    if (thisPort.open(QIODevice::ReadWrite))
    {
        if (thisPort.setBaudRate(SettingsPort.baudRate)
        && thisPort.setDataBits(SettingsPort.dataBits)//DataBits
        && thisPort.setParity(SettingsPort.parity)
        && thisPort.setStopBits(SettingsPort.stopBits)
        && thisPort.setFlowControl(SettingsPort.flowControl))
    {
    if (thisPort.isOpen())
    {
    error_((SettingsPort.name+ " >> Открыт!\r").toLocal8Bit());
    }
} else
        {
    thisPort.close();
    error_(thisPort.errorString().toLocal8Bit());
        }
    } else
    {
thisPort.close();
error_(thisPort.errorString().toLocal8Bit());
}
}


void serialPort::handleError(QSerialPort::SerialPortError error)//
{
if ( (thisPort.isOpen()) && (error == QSerialPort::ResourceError)) {
error_(thisPort.errorString().toLocal8Bit());
DisconnectPort();
}
}//

void serialPort::DisconnectPort(){
if(thisPort.isOpen()){
thisPort.close();
error_(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
}
}

void serialPort :: WriteToPort(QByteArray data){
if(thisPort.isOpen()){
thisPort.write(data);
}
}

void serialPort :: ReadInPort(){
QByteArray data;
data.append(thisPort.readAll());
outPort(data);
}
