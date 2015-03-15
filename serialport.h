#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


struct Settings {
QString name;
qint32 baudRate;
QSerialPort::DataBits dataBits;
QSerialPort::Parity parity;
QSerialPort::StopBits stopBits;
QSerialPort::FlowControl flowControl;
};


class serialPort : public QObject
{
    Q_OBJECT
public:
    explicit serialPort(QObject *parent = 0);
    ~serialPort();    
    QSerialPort thisPort;
    Settings SettingsPort;

signals:
    void finished_Port(); //
   void error_(QString err);
   void outPort(QByteArray data);


public slots:
   void DisconnectPort();
   void ConnectPort(void);
   void Write_Settings_Port(QString name, int baudrate);
   void process_Port();
   void WriteToPort(QByteArray data);
   void ReadInPort();

private slots:
void handleError(QSerialPort::SerialPortError error);//

};

#endif // SERIALPORT_H
