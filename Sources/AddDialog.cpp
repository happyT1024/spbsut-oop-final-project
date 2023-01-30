#include "AddDialog.h"
#include "ui_add_dialog.h"

Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Dialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(" ");
}

Add_Dialog::~Add_Dialog()
{
    delete ui;
}

void Add_Dialog::set_first_name(QString first_name){
    ui->first_name->setText(first_name);
}
void Add_Dialog::set_last_name(QString last_name){
    ui->last_name->setText(last_name);
}
void Add_Dialog::set_patronymic(QString patronymic){
    ui->patronymic->setText(patronymic);
}
void Add_Dialog::set_title(QString title){
    ui->title->setText(title);
}
void Add_Dialog::set_cabinet(QString cabinet){
    ui->cabinet->setText(cabinet);
}

Employee Add_Dialog::getData() {
    Employee result;
    result.set_first_name(ui->first_name->text().simplified());
    result.set_last_name(ui->last_name->text().simplified());
    result.set_patronymic(ui->patronymic->text().simplified());
    result.set_title(ui->title->text().simplified());
    result.set_cabinet(ui->cabinet->text().simplified());
    return result;
}
