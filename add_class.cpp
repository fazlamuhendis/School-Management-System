#include "add_class.h"
#include "ui_add_class.h"

add_class::add_class(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::add_class)
{
    ui->setupUi(this);
}

add_class::~add_class()
{
    delete ui;
}
