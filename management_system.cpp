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

    this->setWindowTitle("School Registration System");

    // Connecting handler slots to button click signals
    connect(ui->btn_import,&QPushButton::clicked,this,&management_system::show_tables);
    connect(ui->btn_update,&QPushButton::clicked,this,&management_system::update_json_file);

    connect(ui->btn_std_table_del,&QPushButton::clicked,this,&management_system::remove_student_member);
    connect(ui->btn_teacher_table_del,&QPushButton::clicked,this,&management_system::remove_teacher_member);
    connect(ui->btn_class_table_del,&QPushButton::clicked,this,&management_system::remove_class_member);
    status_information(status);
}

management_system::~management_system()
{
    delete ui;
}



/* @fn             -show_tables
 *
 * @brief          -Function triggered by import button that tabularly displays values in Json dataset after calling related functions.
 *
 * @param[in]	   -none
 *
 * @return         - none
 */
void management_system::show_tables()
{
        json = read_file("School.json");
        m_currentJsonObject=QtJson::parse(json,ok).toMap();

        if(!ok)
            qFatal("An error occurred during parsing");

        json_school school_list;
        json_vector_list vector_member;

        get_json_dataset(&school_list);
        show_data_set(&school_list,&vector_member);
        status+=1;
        status_information(status);
}


/* @fn             -update_json_file
 *
 * @brief          -It is the function that is triggered by the update button on the interface and
 *                                       calls the relevant functions for these operations after making the relevant addition
 *                                      , deletion and update changes in the table.
 *
 * @param[in]	   -none
 *
 * @return         - none
 */
void management_system::update_json_file()
{
    json_vector_list vector_member;
    get_table_members(&vector_member);
    json_update("School.json",&vector_member);
    status=0;
    status_information(status);
}


/* @fn             -get_json_dataset
 *
 * @brief          -The function that prepares the data taken from the file in order to separate it according to its objects and place it in the related tables.
 *                  Each data is placed in its own JsonObject object.
 *
 * @param[in]	   -The starting address of the list struct that holds and parses the data in the json dataset---Type:json_school
 *
 * @return         - none
 */
void management_system::get_json_dataset(json_school *m_school_list)
{
    m_school_list->result                                          = m_currentJsonObject["school of music"].toMap();

    m_school_list->student_list.result_student                     = m_school_list->result["student"].toMap();
    m_school_list->student_list.result_student_id                  = m_school_list->student_list.result_student["1"].toMap();

    m_school_list->teacher_list.bracnh_name                        = m_school_list->result["teacher"].toMap();
    m_school_list->teacher_list.bracnh_list.result_teacher         = m_school_list->teacher_list.bracnh_name["bracnh"].toMap();
    m_school_list->teacher_list.bracnh_list.result_teacher_lesson  = m_school_list->teacher_list.bracnh_list.result_teacher["music"].toMap();


    m_school_list->class_list.grade_name                           = m_school_list->result["class"].toMap();
    m_school_list->class_list.grade_list.result_grade              = m_school_list->class_list.grade_name["grade"].toMap();
    m_school_list->class_list.grade_list.result_class_grade        = m_school_list->class_list.grade_list.result_grade["1"].toMap();

    ui->students_table->setRowCount(m_school_list->student_list.result_student.count());
    ui->students_table->setColumnCount(m_school_list->student_list.result_student_id.count());
    ui->teachers_table->setRowCount(m_school_list->teacher_list.bracnh_list.result_teacher.count());
    ui->teachers_table->setColumnCount(m_school_list->teacher_list.bracnh_list.result_teacher_lesson.count());
    ui->classes_table->setRowCount(m_school_list->class_list.grade_list.result_grade.count());
    ui->classes_table->setColumnCount(m_school_list->class_list.grade_list.result_class_grade.count());

    ui->students_table->setHorizontalHeaderLabels(QStringList()<<"Surname"<<"Name"<<"Grade"<<"Age"<<"Fee");
    ui->students_table->setVerticalHeaderLabels(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10");
    ui->teachers_table->setHorizontalHeaderLabels(QStringList()<<"Surname"<<"Name"<<"Salary");
    ui->teachers_table->setVerticalHeaderLabels(QStringList()<<"Music"<<"Math"<<"Science"<<"Literature");
    ui->classes_table->setHorizontalHeaderLabels(QStringList()<<"Monday"<<"Tuesday"<<"Wednesday"<<"Thursday"<<"Friday");
    ui->classes_table->setVerticalHeaderLabels(QStringList()<<"1"<<"2");
}


/* @fn             -show_data_set
 *
 * @brief          -A function that allows to import the data successfully placed in the schools list from the file
 *                              , into the vector lists for comfortable processing before placing them in the tables, and adds them to the tables from these vector lists.
 *
 * @param[in]	   -The starting address of the list struct that holds and parses the data in the json dataset---Type:json_school
 * @param[in]      -The starting address of the vectors list struct that allows proper formatting for inserting json addresses into tables.---Type:json-vector_list
 *
 * @return         - none
 */
void management_system::show_data_set(json_school *m_school_list, json_vector_list *m_list)
{
    for(int i=1;i<=m_school_list->student_list.result_student.count();i++)
    {
        m_school_list->student_list.result_student_id=m_school_list->student_list.result_student[QString::number(i)].toMap();
        m_list->student_surname.append(m_school_list->student_list.result_student_id["surname"].toString());
        m_list->student_name.append(m_school_list->student_list.result_student_id["name"].toString());
        m_list->student_grade.append(m_school_list->student_list.result_student_id["grade"].toInt());
        m_list->student_age.append(m_school_list->student_list.result_student_id["age"].toInt());
        m_list->student_fee.append(m_school_list->student_list.result_student_id["fee"].toInt());
    }

    for(int i=1;i<=m_school_list->teacher_list.bracnh_list.result_teacher.count();i++)
    {
        m_school_list->teacher_list.bracnh_list.result_teacher_lesson=m_school_list->teacher_list.bracnh_list.result_teacher[enumaration_teachers(i)].toMap();
        m_list->teacher_surname.append(m_school_list->teacher_list.bracnh_list.result_teacher_lesson["surname"].toString());
        m_list->teacher_name.append(m_school_list->teacher_list.bracnh_list.result_teacher_lesson["name"].toString());
        m_list->teacher_salary.append(m_school_list->teacher_list.bracnh_list.result_teacher_lesson["salary"].toInt());
    }

    for(int i=1;i<=m_school_list->class_list.grade_list.result_grade.count();i++)
    {
        m_school_list->class_list.grade_list.result_class_grade=m_school_list->class_list.grade_list.result_grade[QString::number(i)].toMap();
        m_list->monday_grd.append(m_school_list->class_list.grade_list.result_class_grade["monday"].toString());
        m_list->tuesday_grd.append(m_school_list->class_list.grade_list.result_class_grade["tuesday "].toString());
        m_list->wednesday_grd.append(m_school_list->class_list.grade_list.result_class_grade["wednesday"].toString());
        m_list->thursday_grd.append(m_school_list->class_list.grade_list.result_class_grade["thursday"].toString());
        m_list->friday_grd.append(m_school_list->class_list.grade_list.result_class_grade["friday"].toString());
    }

    for(int i=1;i<=m_school_list->student_list.result_student.count();i++)
    {
        table_list student_table;
        student_table.itm_std_surname = new QTableWidgetItem(m_list->student_surname[i-1]);
        student_table.itm_std_name    = new QTableWidgetItem(m_list->student_name[i-1]);
        student_table.itm_std_grade   = new QTableWidgetItem(QString::number(m_list->student_grade[i-1]));
        student_table.itm_std_age     = new QTableWidgetItem(QString::number(m_list->student_age[i-1]));
        student_table.itm_std_fee     = new QTableWidgetItem(QString::number(m_list->student_fee[i-1]));

        ui->students_table->setItem((i-1),0,student_table.itm_std_surname);
        ui->students_table->setItem((i-1),1,student_table.itm_std_name);
        ui->students_table->setItem((i-1),2,student_table.itm_std_grade);
        ui->students_table->setItem((i-1),3,student_table.itm_std_age);
        ui->students_table->setItem((i-1),4,student_table.itm_std_fee);
    }

    for(int i=1;i<=m_school_list->teacher_list.bracnh_list.result_teacher.count();i++)
    {
        table_list teacher_table;
        teacher_table.itm_tch_surname  = new QTableWidgetItem(m_list->teacher_surname[i-1]);
        teacher_table.itm_tch_name     = new QTableWidgetItem(m_list->teacher_name[i-1]);
        teacher_table.itm_tch_salary   = new QTableWidgetItem(QString::number(m_list->teacher_salary[i-1]));

        ui->teachers_table->setItem((i-1),0,teacher_table.itm_tch_surname);
        ui->teachers_table->setItem((i-1),1,teacher_table.itm_tch_name);
        ui->teachers_table->setItem((i-1),2,teacher_table.itm_tch_salary);
    }

    for(int i=1;i<=m_school_list->class_list.grade_list.result_grade.count();i++){
        table_list class_table;
        class_table.itm_cls_mn         = new QTableWidgetItem(m_list->monday_grd[i-1]);
        class_table.itm_cls_tu         = new QTableWidgetItem(m_list->tuesday_grd[i-1]);
        class_table.itm_cls_wn         = new QTableWidgetItem(m_list->wednesday_grd[i-1]);
        class_table.itm_cls_th         = new QTableWidgetItem(m_list->thursday_grd[i-1]);
        class_table.itm_cls_fr         = new QTableWidgetItem(m_list->friday_grd[i-1]);

        ui->classes_table->setItem((i-1),0,class_table.itm_cls_mn);
        ui->classes_table->setItem((i-1),1,class_table.itm_cls_tu);
        ui->classes_table->setItem((i-1),2,class_table.itm_cls_wn);
        ui->classes_table->setItem((i-1),3,class_table.itm_cls_th);
        ui->classes_table->setItem((i-1),4,class_table.itm_cls_fr);
    }

}


/* @fn             -json_update
 *
 * @brief          -Datasets are created with objects in accordance with the JSON file format of the lists and the data in the lists.
 *
 * @param[in]	   -It takes the file path as a parameter.---Type: const QString
 * @param[in]      -Takes the address of the list name as a parameter.---Type: json_vector_list
 *
 * @return         - none
 */
void management_system::json_update(const QString &fileName,json_vector_list *m_list)
{
    QJsonObject json_school;
    QJsonObject json_school_objects;
    QJsonObject json_school_sub;
    QJsonObject json_school_sub_object_members;
    QJsonObject json_school_sub_object;

    for(int i=0 ;i<ui->students_table->rowCount();i++)
    {
        json_school_sub_object_members.insert("surname",m_list->student_surname.at(i));
        json_school_sub_object_members.insert("name",m_list->student_name.at(i));
        json_school_sub_object_members.insert("grade",m_list->student_grade.at(i));
        json_school_sub_object_members.insert("age",m_list->student_age.at(i));
        json_school_sub_object_members.insert("fee",m_list->student_fee.at(i));
        json_school_sub_object.insert(QString::number(i+1),json_school_sub_object_members);
    }
      json_school_objects.insert("student",json_school_sub_object);

      clearJsonObject(json_school_sub_object_members);
      clearJsonObject(json_school_sub_object);

    for(int i=0;i<ui->teachers_table->rowCount();i++)
    {
        json_school_sub_object_members.insert("surname",m_list->teacher_surname.at(i));
        json_school_sub_object_members.insert("name",m_list->teacher_name.at(i));
        json_school_sub_object_members.insert("salary",m_list->teacher_salary.at(i));
        json_school_sub_object.insert(enumaration_teachers(i+1),json_school_sub_object_members);
    }
    json_school_sub.insert("bracnh",json_school_sub_object);
    json_school_objects.insert("teacher",json_school_sub);

    clearJsonObject(json_school_sub_object_members);
    clearJsonObject(json_school_sub_object);
    clearJsonObject(json_school_sub);

    for(int i=0;i<ui->classes_table->rowCount();i++)
    {
        json_school_sub_object_members.insert("monday",m_list->monday_grd.at(i));
        json_school_sub_object_members.insert("tuesday ",m_list->tuesday_grd.at(i));
        json_school_sub_object_members.insert("wednesday",m_list->wednesday_grd.at(i));
        json_school_sub_object_members.insert("thursday",m_list->thursday_grd.at(i));
        json_school_sub_object_members.insert("friday",m_list->friday_grd.at(i));
        json_school_sub_object.insert(QString::number(i+1),json_school_sub_object_members);
    }
    json_school_sub.insert("grade",json_school_sub_object);
    json_school_objects.insert("class",json_school_sub);
    json_school.insert("school of music",json_school_objects);

    clearJsonObject(json_school_sub_object_members);
    clearJsonObject(json_school_sub_object);
    clearJsonObject(json_school_objects);
    clearJsonObject(json_school_sub);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(json_school);
    QByteArray byteArray=jsonDocument.toJson(QJsonDocument::Indented);

    write_file(fileName,byteArray);
}


/* @fn             -get_table_members
 *
 * @brief          -After clearing the lists, it takes the values in the table into the relevant lists, these lists can be thought of as a buffer.
 *
 * @param[in]	   -address of the list to be entered--type:json_vector_list
 *
 * @return         - none
 */
void management_system::get_table_members(json_vector_list *m_list)
{
    m_list->student_name.clear();
    m_list->student_surname.clear();
    m_list->student_grade.clear();
    m_list->student_fee.clear();
    m_list->student_age.clear();

    m_list->teacher_surname.clear();
    m_list->teacher_surname.clear();
    m_list->teacher_salary.clear();

    m_list->monday_grd.clear();
    m_list->tuesday_grd.clear();
    m_list->wednesday_grd.clear();
    m_list->thursday_grd.clear();
    m_list->friday_grd.clear();

    for(int i=0;i<ui->students_table->rowCount();i++)
    {
        m_list->student_surname.append(ui->students_table->model()->index(i,0).data().toString());
        m_list->student_name.append(ui->students_table->model()->index(i,1).data().toString());
        m_list->student_grade.append(ui->students_table->model()->index(i,2).data().toInt());
        m_list->student_age.append(ui->students_table->model()->index(i,3).data().toInt());
        m_list->student_fee.append(ui->students_table->model()->index(i,4).data().toInt());
    }

    for(int i=0;i<ui->teachers_table->rowCount();i++)
    {
        m_list->teacher_surname.append(ui->teachers_table->model()->index(i,0).data().toString());
        m_list->teacher_name.append(ui->teachers_table->model()->index(i,1).data().toString());
        m_list->teacher_salary.append(ui->teachers_table->model()->index(i,2).data().toInt());
    }

    for(int i=0;i<ui->classes_table->rowCount();i++)
    {
        m_list->monday_grd.append(ui->classes_table->model()->index(i,0).data().toString());
        m_list->tuesday_grd.append(ui->classes_table->model()->index(i,1).data().toString());
        m_list->wednesday_grd.append(ui->classes_table->model()->index(i,2).data().toString());
        m_list->thursday_grd.append(ui->classes_table->model()->index(i,3).data().toString());
        m_list->friday_grd.append(ui->classes_table->model()->index(i,4).data().toString());
    }
}




/* @fn             -read_file
 *
 * @brief          -It is a function that takes the data in the file as String by entering the file path.
 *
 * @param[in]	   -Takes the path of the file as a parameter.---Type:const QString
 *
 * @return         -Data read from file
 */
QString management_system::read_file(const QString &filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        return QString();
    } else {
        QTextStream in(&f);
        return in.readAll();
    }
}

/* @fn             -write_file
 *
 * @brief          -If a data is to be written to any file, after entering the file path and bytearray array parameters to be printed,
 *                 it is the function that creates the file, writes the value into it, and then closes the file.
 *
 * @param[in]	   -Takes the file name to be written as a parameter.---Type : const QString
 * @param[in]	   -The format to be written to the file is kept as a byte array. ---Type:QByteArray
 *
 *
 * @return         - true or false
 */
bool management_system::write_file(const QString &filename,QByteArray byteArray)
{
    QFile f(filename);
    if(!f.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        QMessageBox::critical(this,"Error!","Could not create file at this path.");
        return -1;
    }else{
        QTextStream stream(&f);
        stream<<byteArray;
        f.close();
        ui->statusbar->showMessage("Updated the json dataset file.");
    }
}


/* @fn             -get_table_members
 *
 * @brief          -Cleans and empties the object containing data.
 *
 * @param[in]	   -address object --- type: QJsonObject
 *
 * @return         - none
 */
void management_system::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();
    for(int i = 0; i < strList.size(); ++i)
    {
        object.remove(strList.at(i));
    }
}


/* @fn             -enumaration_teachers
 *
 * @brief          -It is the function that gives information about which teacher the lesson belongs to in the teachers class for smarter sorting.
 *
 * @param[in]	   -It takes the class number in our dataset as a parameter.---Tpye:int
 *
 * @return         - QString : Which subject the teacher is the teacher of.
 */
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
    }
}


/* @fn             -remove_student_member,remove_teacher_member,remove_class_member
 *
 * @brief          -Button-triggered functions that delete the marked row in tables.
 *
 * @param[in]	   -none
 *
 * @return         - none
 */
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


/* @fn             -status_information
 *
 * @brief          -A function that specifies which button will be active and which will not, according to the value of the state variable.
 *
 * @param[in]	   -status program.---Type:int
 *
 * @return         - none
 */
void management_system::status_information(int val)
{
    if(val==0)
    {
        ui->btn_import->setEnabled(true);
        ui->btn_update->setEnabled(false);
        ui->btn_st_table_add->setEnabled(false);
        ui->btn_std_table_del->setEnabled(false);
        ui->btn_teacher_table_add->setEnabled(false);
        ui->btn_teacher_table_del->setEnabled(false);
        ui->btn_class_table_add->setEnabled(false);
        ui->btn_class_table_del->setEnabled(false);
        ui->students_table->setEnabled(false);
        ui->teachers_table->setEnabled(false);
        ui->classes_table->setEnabled(false);
    }
    else if (val==1)
    {
        ui->btn_import->setEnabled(false);
        ui->btn_update->setEnabled(true);
        ui->btn_st_table_add->setEnabled(true);
        ui->btn_std_table_del->setEnabled(true);
        ui->btn_teacher_table_add->setEnabled(true);
        ui->btn_teacher_table_del->setEnabled(true);
        ui->btn_class_table_add->setEnabled(true);
        ui->btn_class_table_del->setEnabled(true);
        ui->students_table->setEnabled(true);
        ui->teachers_table->setEnabled(true);
        ui->classes_table->setEnabled(true);
    }
}


/* @fn             -on_btn_st_table_add_clicked,on_btn_teacher_table_add_clicked,on_btn_class_table_add_clicked
 *
 * @brief          -Button-triggered functions that add the marked row in tables.
 *
 * @param[in]	   -none
 *
 * @return         -none
 */
void management_system::on_btn_st_table_add_clicked()
{
    ui->students_table->insertRow(ui->students_table->rowCount());
}

void management_system::on_btn_teacher_table_add_clicked()
{
    ui->teachers_table->insertRow(ui->teachers_table->rowCount());
}

void management_system::on_btn_class_table_add_clicked()
{
    ui->classes_table->insertRow(ui->classes_table->rowCount());
}
