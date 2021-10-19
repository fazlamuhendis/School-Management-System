#include "add_teacher.h"
#include "ui_add_teacher.h"

add_teacher::add_teacher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::add_teacher)
{
    ui->setupUi(this);
}

add_teacher::~add_teacher()
{
    delete ui;
}
