#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "serialport.h"
#include <QSettings>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pbtopen_clicked();

    void on_pbtupdate_clicked();

private:
    Ui::Form *ui;
    serialPort *ser;
    QSerialPortInfo *portinfo;
    QSettings *set;
    void closeEvent(QCloseEvent *event);
};

#endif // FORM_H
