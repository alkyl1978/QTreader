#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>

typedef struct
{
    qint8 start_pak;
    qint8 count;
    qint8 dat;
    qint16 cn;
    qint16 cn_p;
    qint16 dat_time;
    qint16 crc;
} pak_def;


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
signals:
   void finished_Port(); //
   void error_(QString err);
   void outPort(QByteArray data);
   void closePort();
   void openPort();


public slots:
   void DisconnectPort();
   void ConnectPort();
   void process_Port();
   void WriteToPort(QByteArray data);
   void ReadInPort();
   void changePort(QString name);
   void changebaud(QString baund);


private slots:
void handleError(QSerialPort::SerialPortError error);//

};

#endif // SERIALPORT_H
