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

    this->setWindowTitle("Management School System");

    // Connecting handler slots to button click signals
    connect(ui->btn_import,&QPushButton::clicked,this,&management_system::show_tables);
    connect(ui->btn_update,&QPushButton::clicked,this,&management_system::update_json_file);

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

      /*  QtJson::JsonObject obj = QtJson::objectBuilder()
                ->set("school of music",QtJson::objectBuilder()
                      ->set("student",QtJson::objectBuilder()
                            ->set("1",QtJson::objectBuilder()
                                  ->set("surname","korkmaz")
                                  ->set("name","sinan")
                                  ->set("grade","2")
                                  ->set("age","7")
                                  ->set("fee","60000"))))
                            ->create();
       writeFile("School",obj);                */
}

void management_system::update_json_file()
{
    json_vector_list vector_member;

    vector_member.student_name.clear();
    vector_member.student_surname.clear();
    vector_member.student_grade.clear();
    vector_member.student_fee.clear();
    vector_member.student_age.clear();

    vector_member.teacher_surname.clear();
    vector_member.teacher_surname.clear();
    vector_member.teacher_salary.clear();

    vector_member.monday_grd.clear();
    vector_member.tuesday_grd.clear();
    vector_member.wednesday_grd.clear();
    vector_member.thursday_grd.clear();
    vector_member.friday_grd.clear();

    for(int i=0;i<ui->students_table->rowCount();i++)
    {
        vector_member.student_surname.append(ui->students_table->model()->index(i,0).data().toString());
        vector_member.student_name.append(ui->students_table->model()->index(i,1).data().toString());
        vector_member.student_grade.append(ui->students_table->model()->index(i,2).data().toInt());
        vector_member.student_age.append(ui->students_table->model()->index(i,3).data().toInt());
        vector_member.student_fee.append(ui->students_table->model()->index(i,4).data().toInt());
    }

    for(int i=0;i<ui->teachers_table->rowCount();i++)
    {
        vector_member.teacher_surname.append(ui->teachers_table->model()->index(i,0).data().toString());
        vector_member.teacher_name.append(ui->teachers_table->model()->index(i,1).data().toString());
        vector_member.teacher_salary.append(ui->teachers_table->model()->index(i,2).data().toInt());
    }

    for(int i=0;i<ui->classes_table->rowCount();i++)
    {
        vector_member.monday_grd.append(ui->classes_table->model()->index(i,0).data().toString());
        vector_member.tuesday_grd.append(ui->classes_table->model()->index(i,1).data().toString());
        vector_member.wednesday_grd.append(ui->classes_table->model()->index(i,2).data().toString());
        vector_member.thursday_grd.append(ui->classes_table->model()->index(i,3).data().toString());
        vector_member.friday_grd.append(ui->classes_table->model()->index(i,4).data().toString());
    }
    qDebug()<<vector_member.student_age.length();

    QJsonObject json_school;
    QJsonObject json_student;
    QJsonObject json_teacher;
    QJsonObject json_class;
    QJsonObject student_id;
    QJsonObject student_fealuare;
    QJsonObject teacher_bracnh;
    QJsonObject teacher_lessons;
    QJsonObject teacher_fealuare;
    QJsonObject classs_grade;
    QJsonObject grade_name;
    QJsonObject gradee_fealuare;
    QJsonObject meh;
    for(int i=0 ;i<ui->students_table->rowCount();i++)
    {
        student_fealuare.insert("surname",vector_member.student_surname.at(i));
        student_fealuare.insert("name",vector_member.student_name.at(i));
        student_fealuare.insert("grade",vector_member.student_grade.at(i));
        student_fealuare.insert("age",vector_member.student_age.at(i));
        student_fealuare.insert("fee",vector_member.student_fee.at(i));
        student_id.insert(QString::number(i+1),student_fealuare);
    }
    //json_student.insert("student",student_id);
      meh.insert("student",student_id);
      json_school.insert("school of music",meh);
     // clearJsonObject(meh);
    for(int i=0;i<ui->teachers_table->rowCount();i++)
    {
        teacher_fealuare.insert("surname",vector_member.teacher_surname.at(i));
        teacher_fealuare.insert("name",vector_member.teacher_name.at(i));
        teacher_fealuare.insert("salary",vector_member.teacher_salary.at(i));
        teacher_lessons.insert(enumaration_teachers(i+1),teacher_fealuare);
    }
    teacher_bracnh.insert("bracnh",teacher_lessons);
    //json_teacher.insert("teacher",teacher_bracnh);
    meh.insert("teacher",teacher_bracnh);
    json_school.insert("school of music",meh);
   // clearJsonObject(meh);


    for(int i=0;i<ui->classes_table->rowCount();i++)
    {
        gradee_fealuare.insert("monday",vector_member.monday_grd.at(i));
        gradee_fealuare.insert("tuesday ",vector_member.tuesday_grd.at(i));
        gradee_fealuare.insert("wednesday",vector_member.wednesday_grd.at(i));
        gradee_fealuare.insert("thursday",vector_member.thursday_grd.at(i));
        gradee_fealuare.insert("friday",vector_member.friday_grd.at(i));
        grade_name.insert(QString::number(i+1),gradee_fealuare);
    }
    classs_grade.insert("grade",grade_name);
    //json_class.insert("class",classs_grade);
    meh.insert("class",classs_grade);
    json_school.insert("school of music",meh);
   // clearJsonObject(meh);
    //json_school.insert("school of music",QJsonObject(json_student));
    //json_school.insert("school of music",QJsonObject(json_teacher));

    //json_school.insert("school of music",json_student);
   // json_school.insert("school of music",json_class);
   // json_school.insert("school of music",json_teacher);


    QJsonDocument jsonDocument;
    jsonDocument.setObject(json_school);
    QByteArray byteArray=jsonDocument.toJson(QJsonDocument::Indented);
    QString filename = "Reis.json";
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QTextStream out(&file);
    out << byteArray;
    file.close();
    qDebug() << byteArray;


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

bool management_system::writeFile(const QString &filename,QString json_dataset)
{
    QFile f(filename);
    if(!f.open(QFile::WriteOnly | QFile::Text)){
        return false;
    }else{
        QTextStream stream(&f);
        stream<<json_dataset;
        return true;
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

void management_system::json_olustur(const QString &fileName)
{
    QJsonArray jsonArray;
    QJsonObject rootObject;
    QJsonObject branchObject;
    QJsonObject leafObject;
    leafObject.insert("quality", 18.2);
    leafObject.insert("temp", 25.0);
    branchObject.insert("I1", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("quality", 2000);
    leafObject.insert("temp", 20.0);
    branchObject.insert("I2", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("value", 98);
    branchObject.insert("RO Rejection", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("value", 3);
    branchObject.insert("TOC", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    rootObject.insert("heartData", jsonArray);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(rootObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QTextStream out(&file);
    out << byteArray;
    file.close();
    qDebug() << byteArray;

}

void management_system::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();
    for(int i = 0; i < strList.size(); ++i)
    {
        object.remove(strList.at(i));
    }
}




void management_system::on_pushButton_clicked()
{
    json_olustur("Sinan.json");
}
