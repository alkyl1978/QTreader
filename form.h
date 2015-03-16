#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "serialport.h"
#include <QSettings>
#include <QThread>
#include <QTimerEvent>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
signals:
    void writeData(QByteArray data);

private slots:
    void on_pbtupdate_clicked();
    void Print(QByteArray data);
    void closeport();
    void openport();

private:
    Ui::Form *ui;
    serialPort *ser;
    QSerialPortInfo *portinfo;
    QSettings *set;
    void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *event);
    int timer;
    QByteArray arr_out;
};

#endif // FORM_H
