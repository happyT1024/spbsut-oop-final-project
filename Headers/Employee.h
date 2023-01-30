#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QVector>

class Employee
{
private:
    QString _first_name;
    QString _last_name;
    QString _patronymic;
    QString _title;
    QString _cabinet;
public:
    Employee(QString first_name = "",
             QString last_name = "",
             QString patronymic = "",
             QString title = "",
             QString cabinet = "")
        :_first_name(first_name)
        ,_last_name(last_name)
        ,_patronymic(patronymic)
        ,_title(title)
        ,_cabinet(cabinet)
    {}

    void set_first_name(QString first_name);
    void set_last_name(QString last_name);
    void set_patronymic(QString patronymic);
    void set_title(QString title);
    void set_cabinet(QString cabinet);

    QString get_first_name();
    QString get_last_name();
    QString get_patronymic();
    QString get_title();
    QString get_cabinet();

    QVector<QString> get_employee();
};

#endif // EMPLOYEE_H
