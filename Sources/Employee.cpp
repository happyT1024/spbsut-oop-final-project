#include "Employee.h"

void Employee::set_first_name(QString first_name){
    _first_name = first_name;
}

void Employee::set_last_name(QString last_name){
    _last_name = last_name;
}

void Employee::set_patronymic(QString patronymic){
    _patronymic = patronymic;
}

void Employee::set_title(QString title){
    _title = title;
}

void Employee::set_cabinet(QString cabinet){
    _cabinet = cabinet;
}

QString Employee::get_first_name(){
    return _first_name;
}

QString Employee::get_last_name(){
    return _last_name;
}

QString Employee::get_patronymic(){
    return _patronymic;
}

QString Employee::get_title(){
    return _title;
}

QString Employee::get_cabinet(){
    return _cabinet;
}

QVector<QString> Employee::get_employee(){
    return QVector<QString>{_last_name, _first_name, _patronymic, _cabinet, _title};
}

