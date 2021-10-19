#ifndef ADD_TEACHER_H
#define ADD_TEACHER_H

#include <QMainWindow>

namespace Ui {
class add_teacher;
}

class add_teacher : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_teacher(QWidget *parent = nullptr);
    ~add_teacher();

private:
    Ui::add_teacher *ui;
};

#endif // ADD_TEACHER_H
