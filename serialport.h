#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>


class serialPort : public QObject
{
    Q_OBJECT
public:
    explicit serialPort(QObject *parent = 0);
    ~serialPort();    
    QSerialPort *thisPort;
private:
    QSettings *seting;
    QString name;
    qint32 baudRate;
    QSerialPortInfo *portinfo;
signals:
   void finished_Port(); //
   void error_(QString err);
   void outPort(QByteArray data);
   void isvalid();


public slots:
   void DisconnectPort();
   void ConnectPort();
   void process_Port();
   void WriteToPort(QByteArray data);
   void ReadInPort();
   void toClose();
   void changePort(QString name);
   void changebaud(QString baund);


private slots:
void handleError(QSerialPort::SerialPortError error);//

};

#endif // SERIALPORT_H
