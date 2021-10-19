#include "add_student.h"
#include "ui_add_student.h"

add_student::add_student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::add_student)
{
    ui->setupUi(this);
}

add_student::~add_student()
{
    delete ui;
}
