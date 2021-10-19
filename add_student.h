#ifndef ADD_STUDENT_H
#define ADD_STUDENT_H

#include <QMainWindow>

namespace Ui {
class add_student;
}

class add_student : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_student(QWidget *parent = nullptr);
    ~add_student();

private:
    Ui::add_student *ui;
};

#endif // ADD_STUDENT_H
