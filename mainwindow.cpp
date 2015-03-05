#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QList<QSerialPortInfo> com_ports = QSerialPortInfo::availablePorts();
    QSerialPortInfo port;
    ui->setupUi(this);
    foreach(port, com_ports)
    {
        ui->comboBox->addItem(port.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
