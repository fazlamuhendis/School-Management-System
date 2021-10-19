/*
 * managemeng_system.cpp
 *
 *
 *  Created on: October 13, 2021
 *  Author: Sinan Reis KORKMAZ
 *
 * @brief : File containing main widget source codes from which table tabs, dataset file can be imported and updated, tables can be viewed, elements can be added and elements deleted.
 */

#include "management_system.h"
#include "ui_management_system.h"
#include <QStringList>
#include <QDebug>

management_system::management_system(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::management_system)
{
    ui->setupUi(this);


    // Connecting handler slots to button click signals
    connect(ui->btn_import,&QPushButton::clicked,this,&management_system::show_tables);

    connect(ui->btn_std_table_del,&QPushButton::clicked,this,&management_system::remove_student_member);
    connect(ui->btn_teacher_table_del,&QPushButton::clicked,this,&management_system::remove_teacher_member);
    connect(ui->btn_class_table_del,&QPushButton::clicked,this,&management_system::remove_class_member);
    connect(ui->btn_st_table_add,&QPushButton::clicked,this,&management_system::dizide_tut);
}

management_system::~management_system()
{
    delete ui;
}



void management_system::on_btn_quit_clicked()
{
    this->close();
}

void management_system::show_tables()
{
    //Jsondan veriyi çekme
        json = readFile("School.json");
        m_currentJsonObject=QtJson::parse(json,ok).toMap();

        if(!ok)
            qFatal("An error occurred during parsing");

        json_school school_list;
        school_list.result                                          = m_currentJsonObject["school of music"].toMap();

        school_list.student_list.result_student                     = school_list.result["student"].toMap();
        school_list.student_list.result_student_id                  = school_list.student_list.result_student["1"].toMap();

        school_list.teacher_list.bracnh_name                        = school_list.result["teacher"].toMap();
        school_list.teacher_list.bracnh_list.result_teacher         = school_list.teacher_list.bracnh_name["bracnh"].toMap();
        school_list.teacher_list.bracnh_list.result_teacher_lesson  = school_list.teacher_list.bracnh_list.result_teacher["music"].toMap();


        school_list.class_list.grade_name                           = school_list.result["class"].toMap();
        school_list.class_list.grade_list.result_grade              = school_list.class_list.grade_name["grade"].toMap();
        school_list.class_list.grade_list.result_class_grade        = school_list.class_list.grade_list.result_grade["1"].toMap();

        ui->students_table->setRowCount(school_list.student_list.result_student.count());
        ui->students_table->setColumnCount(school_list.student_list.result_student_id.count());
        ui->teachers_table->setRowCount(school_list.teacher_list.bracnh_list.result_teacher.count());
        ui->teachers_table->setColumnCount(school_list.teacher_list.bracnh_list.result_teacher_lesson.count());
        ui->classes_table->setRowCount(school_list.class_list.grade_list.result_grade.count());
        ui->classes_table->setColumnCount(school_list.class_list.grade_list.result_class_grade.count());

        ui->students_table->setHorizontalHeaderLabels(QStringList()<<"Surname"<<"Name"<<"Grade"<<"Age"<<"Fee");
        ui->students_table->setVerticalHeaderLabels(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10");
        ui->teachers_table->setHorizontalHeaderLabels(QStringList()<<"Surname"<<"Name"<<"Salary");
        ui->teachers_table->setVerticalHeaderLabels(QStringList()<<"Music"<<"Math"<<"Science"<<"Literature");
        ui->classes_table->setHorizontalHeaderLabels(QStringList()<<"Monday"<<"Tuesday"<<"Wednesday"<<"Thursday"<<"Friday");
        ui->classes_table->setVerticalHeaderLabels(QStringList()<<"Grade 1"<<"Grade 2");


        //Vektör dızısıne alma
        json_vector_list vector_member;
        for(int i=1;i<=school_list.student_list.result_student.count();i++)
        {
            school_list.student_list.result_student_id=school_list.student_list.result_student[QString::number(i)].toMap();
            vector_member.student_surname.append(school_list.student_list.result_student_id["surname"].toString());
            vector_member.student_name.append(school_list.student_list.result_student_id["name"].toString());
            vector_member.student_grade.append(school_list.student_list.result_student_id["grade"].toInt());
            vector_member.student_age.append(school_list.student_list.result_student_id["age"].toInt());
            vector_member.student_fee.append(school_list.student_list.result_student_id["fee"].toInt());
        }

        for(int i=1;i<=school_list.teacher_list.bracnh_list.result_teacher.count();i++)
        {
            school_list.teacher_list.bracnh_list.result_teacher_lesson=school_list.teacher_list.bracnh_list.result_teacher[enumaration_teachers(i)].toMap();
            vector_member.teacher_surname.append(school_list.teacher_list.bracnh_list.result_teacher_lesson["surname"].toString());
            vector_member.teacher_name.append(school_list.teacher_list.bracnh_list.result_teacher_lesson["name"].toString());
            vector_member.teacher_salary.append(school_list.teacher_list.bracnh_list.result_teacher_lesson["salary"].toInt());
        }

        for(int i=1;i<=school_list.class_list.grade_list.result_grade.count();i++)
        {
            school_list.class_list.grade_list.result_class_grade=school_list.class_list.grade_list.result_grade[QString::number(i)].toMap();
            vector_member.monday_grd.append(school_list.class_list.grade_list.result_class_grade["monday"].toString());
            vector_member.tuesday_grd.append(school_list.class_list.grade_list.result_class_grade["tuesday "].toString());
            vector_member.wednesday_grd.append(school_list.class_list.grade_list.result_class_grade["wednesday"].toString());
            vector_member.thursday_grd.append(school_list.class_list.grade_list.result_class_grade["thursday"].toString());
            vector_member.friday_grd.append(school_list.class_list.grade_list.result_class_grade["friday"].toString());
        }

        //Tabloya yerlestırme
        for(int i=1;i<=school_list.student_list.result_student.count();i++)
        {
            table_list student_table;
            student_table.itm_std_surname = new QTableWidgetItem(vector_member.student_surname[i-1]);
            student_table.itm_std_name    = new QTableWidgetItem(vector_member.student_name[i-1]);
            student_table.itm_std_grade   = new QTableWidgetItem(QString::number(vector_member.student_grade[i-1]));
            student_table.itm_std_age     = new QTableWidgetItem(QString::number(vector_member.student_age[i-1]));
            student_table.itm_std_fee     = new QTableWidgetItem(QString::number(vector_member.student_fee[i-1]));

            ui->students_table->setItem((i-1),0,student_table.itm_std_surname);
            ui->students_table->setItem((i-1),1,student_table.itm_std_name);
            ui->students_table->setItem((i-1),2,student_table.itm_std_grade);
            ui->students_table->setItem((i-1),3,student_table.itm_std_age);
            ui->students_table->setItem((i-1),4,student_table.itm_std_fee);
        }

        for(int i=1;i<=school_list.teacher_list.bracnh_list.result_teacher.count();i++)
        {
            table_list teacher_table;
            teacher_table.itm_tch_surname  = new QTableWidgetItem(vector_member.teacher_surname[i-1]);
            teacher_table.itm_tch_name     = new QTableWidgetItem(vector_member.teacher_name[i-1]);
            teacher_table.itm_tch_salary   = new QTableWidgetItem(QString::number(vector_member.teacher_salary[i-1]));

            ui->teachers_table->setItem((i-1),0,teacher_table.itm_tch_surname);
            ui->teachers_table->setItem((i-1),1,teacher_table.itm_tch_name);
            ui->teachers_table->setItem((i-1),2,teacher_table.itm_tch_salary);
        }

        for(int i=1;i<=school_list.class_list.grade_list.result_grade.count();i++){
            table_list class_table;
            class_table.itm_cls_mn         = new QTableWidgetItem(vector_member.monday_grd[i-1]);
            class_table.itm_cls_tu         = new QTableWidgetItem(vector_member.tuesday_grd[i-1]);
            class_table.itm_cls_wn         = new QTableWidgetItem(vector_member.wednesday_grd[i-1]);
            class_table.itm_cls_th         = new QTableWidgetItem(vector_member.thursday_grd[i-1]);
            class_table.itm_cls_fr         = new QTableWidgetItem(vector_member.friday_grd[i-1]);

            ui->classes_table->setItem((i-1),0,class_table.itm_cls_mn);
            ui->classes_table->setItem((i-1),1,class_table.itm_cls_tu);
            ui->classes_table->setItem((i-1),2,class_table.itm_cls_wn);
            ui->classes_table->setItem((i-1),3,class_table.itm_cls_th);
            ui->classes_table->setItem((i-1),4,class_table.itm_cls_fr);
        }
}

void management_system::remove_student_member()
{
    ui->students_table->removeRow(ui->students_table->currentRow());
}

void management_system::remove_teacher_member()
{
    ui->teachers_table->removeRow(ui->teachers_table->currentRow());
}

void management_system::remove_class_member()
{
    ui->classes_table->removeRow(ui->classes_table->currentRow());
}

void management_system::dizide_tut()
{
    ui->students_table->insertRow(ui->students_table->rowCount());

}

QString management_system::readFile(const QString &filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        qDebug()<<"basarısız";
        return QString();
    } else {
        QTextStream in(&f);
        return in.readAll();
    }
}

QString management_system::enumaration_teachers(int class_num)
{
    if(class_num==1){
        return "music";
    }else if(class_num==2){
        return "math";
    }else if(class_num==3){
        return "science";
    }else if(class_num==4){
        return "literature";
    }else{
     return 0; //bişeyler eklenebilir
    }
}


void management_system::set_student_table()
{

}

void management_system::on_btn_st_table_add_clicked()
{
    m_student=new add_student(this) ;
    m_student->show();
}

void management_system::on_btn_teacher_table_add_clicked()
{
    m_teacher=new add_teacher(this);
    m_teacher->show();
}

void management_system::on_btn_class_table_add_clicked()
{
    m_class=new add_class(this);
    m_class->show();
}
