#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ser=new serialPort(this);
    set=new QSettings("MyCompany", "MyApp");
    this->restoreGeometry(set->value("geometr").toByteArray());
}

Form::~Form()
{
    delete ui;
}

void Form::closeEvent(QCloseEvent *)
{
    set->setValue("geometr",saveGeometry());
    return;
}
