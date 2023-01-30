#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "Employee.h"

namespace Ui {
    class Add_Dialog;
}

class Add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Dialog(QWidget *parent = nullptr);
    ~Add_Dialog();
    Employee getData();
    void set_first_name(QString first_name);
    void set_last_name(QString last_name);
    void set_patronymic(QString patronymic);
    void set_title(QString title);
    void set_cabinet(QString cabinet);

private:
    Ui::Add_Dialog *ui;
};

#endif // ADDDIALOG_H
