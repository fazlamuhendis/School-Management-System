#ifndef MANAGEMENT_SYSTEM_H
#define MANAGEMENT_SYSTEM_H

#include <QMainWindow>

#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QIODevice>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "json.h"

QT_BEGIN_NAMESPACE
namespace Ui { class management_system;}
QT_END_NAMESPACE

class management_system : public QMainWindow
{
    Q_OBJECT

public:
    management_system(QWidget *parent = nullptr);
    ~management_system();

private slots:
    void on_btn_quit_clicked();

private:
    Ui::management_system *ui;

    QString json;

    bool ok;

    void show_tables();

    void update_json_file();

    //remove functions
    void remove_student_member();

    void remove_teacher_member();

    void remove_class_member();


    QString read_file(const QString &filename);

    bool write_file(const QString &filename,QByteArray byteArray);

    QString enumaration_teachers(int class_num);

    QtJson::JsonObject m_currentJsonObject;

    void clearJsonObject(QJsonObject &object);


    typedef struct
        {
        QtJson::JsonObject result_teacher;
        QtJson::JsonObject result_teacher_lesson;
        QtJson::JsonObject tch_surname;
        QtJson::JsonObject tch_name;
        QtJson::JsonObject tch_salary;
        }json_teacher_bracnh;

    typedef struct
    {
        QtJson::JsonObject result_grade;
        QtJson::JsonObject result_class_grade;
        QtJson::JsonObject clss_grade1;
        QtJson::JsonObject clss_grade2;
    }json_class_grade;

    typedef struct
    {
        QtJson::JsonObject grade_name;
        json_class_grade grade_list;
    }json_class;

    typedef struct
    {
        QtJson::JsonObject bracnh_name;
        json_teacher_bracnh bracnh_list;
    }json_teacher;

    typedef struct
    {
        QtJson::JsonObject result_student_id;
        QtJson::JsonObject result_student;
        QtJson::JsonObject st_surname;
        QtJson::JsonObject st_name;
        QtJson::JsonObject st_grade;
        QtJson::JsonObject st_age;
        QtJson::JsonObject st_fee;
    }json_student;


    typedef struct
    {
        QtJson::JsonObject result;
        json_student student_list;
        json_class class_list;
        json_teacher teacher_list;
    }json_school;

    typedef struct{
        QVector<int> student_age;
        QVector<int> student_fee;
        QVector<int> student_grade;
        QVector<QString> student_surname;
        QVector<QString> student_name;

        QVector<QString> teacher_surname;
        QVector<QString> teacher_name;
        QVector<int> teacher_salary;

        QVector<QString> monday_grd;
        QVector<QString> tuesday_grd;
        QVector<QString> wednesday_grd;
        QVector<QString> thursday_grd;
        QVector<QString> friday_grd;
    }json_vector_list;

    typedef struct
    {
       QTableWidgetItem *itm_std_surname;
       QTableWidgetItem *itm_std_name;
       QTableWidgetItem *itm_std_age;
       QTableWidgetItem *itm_std_fee;
       QTableWidgetItem *itm_std_grade;

       QTableWidgetItem *itm_tch_surname;
       QTableWidgetItem *itm_tch_name;
       QTableWidgetItem *itm_tch_salary;

       QTableWidgetItem *itm_cls_mn;
       QTableWidgetItem *itm_cls_tu;
       QTableWidgetItem *itm_cls_wn;
       QTableWidgetItem *itm_cls_th;
       QTableWidgetItem *itm_cls_fr;
    }table_list;


    void get_json_dataset(json_school *m_school_list);
    void show_data_set(json_school *m_school_list,json_vector_list *m_list);
    void json_update(const QString &fileName,json_vector_list *m_list);
    void get_table_members(json_vector_list *m_list);
};
#endif // MANAGEMENT_SYSTEM_H
