#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "AddDialog.h"
#include "ShowData.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include "Vector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите создать новый файл?\nВсе проделанные изменения не будут сохранены.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    ui->tableWidget->setRowCount(0);
    data_base = DLinkedList<Employee>();
    file_ = "";
    setWindowTitle("*" + file_ + " – " + program_name);
}

void MainWindow::on_action_Exit_triggered()
{
    if (ui->tableWidget->rowCount() > 0 || file_ != "") {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите выйти?\nВсе проделанные изменения не будут сохранены.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    exit(0);
}

// О программе
void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,
                       "О программе",
                       "Курсовая работа по дисциплине ООП\n"
                       "Объектно-ориентированное программирование\n"
                       "Тема: Класс, характеризующий сотрудника предприятия\n"
                       "Вариант 2\n"
                       "Выполнил студент группы ИКПИ-12\n"
                       "Суменков Матвей");
}

void MainWindow::on_action_Add_triggered()
{
    Add_Dialog add_dialog;
    if (add_dialog.exec() == QDialog::Accepted)
    {
        Employee employee = add_dialog.getData();
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        int i=0;
        for(auto item:employee.get_employee()){
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i, new QTableWidgetItem(item));
            i++;
        }
        data_base.push_back(employee);
        ui->statusBar->showMessage("Запись добавлена");
        setWindowTitle("*" + file_ + " – " + program_name);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setCurrentCell(-1, -1);
    if (arg1 == "") {
        return;
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    auto find_items = ui->tableWidget->findItems(arg1, Qt::MatchContains);
    int len = find_items.size();
    for (int i = 0; i < len; ++i) {
        auto item = find_items.at(i);
        ui->tableWidget->setItemSelected(item, true);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->statusBar->showMessage("Найдено " + QString::number(len) + " ячеек");
}

void MainWindow::on_action_Edit_triggered()
{
    auto list = ui->tableWidget->selectedItems();
    if (list.size() > 0) {
        Add_Dialog add_dialog;
        add_dialog.set_last_name(list.at(0)->text());
        add_dialog.set_first_name(list.at(1)->text());
        add_dialog.set_patronymic(list.at(2)->text());
        add_dialog.set_cabinet(list.at(3)->text());
        add_dialog.set_title(list.at(4)->text());
        if (add_dialog.exec() == QDialog::Accepted)
        {
            int i=0;
            Employee employee = add_dialog.getData();
            for(auto item:employee.get_employee()){
                list.at(i)->setText(item);
                i++;
            }
            data_base.changeValue(list.at(0)->row(),employee);
            setWindowTitle("*" + file_ + " – " + program_name);
        }
    }
}

void MainWindow::on_action_Delete_triggered()
{
    auto list = ui->tableWidget->selectionModel()->selectedRows();
    if (list.size() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите удалить строки с выбранными элементами?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            for (auto k = list.rbegin(); k != list.rend(); ++k) {
                int idx = (*k).row();
                data_base.erase(idx);
                ui->tableWidget->removeRow(idx);
            }
            ui->statusBar->showMessage("Запись удалена");
            setWindowTitle("*" + file_ + " – " + program_name);
        }
    } else ui->statusBar->showMessage("Таблица пуста");
}

void MainWindow::on_action_Clear_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите очистить таблицу?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->tableWidget->setRowCount(0);
            data_base = DLinkedList<Employee>();
            ui->statusBar->showMessage("Таблица очищена");
            setWindowTitle("*" + file_ + " – " + program_name);
        }
    } else ui->statusBar->showMessage("Таблица пуста");
}

void MainWindow::on_action_Open_triggered(bool isClean)
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile()) {
        if (isClean) {
            MainWindow::on_action_New_triggered();
        }
        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Employee employee;
                QStringList list = in.readLine().split(";");
                if(list.size()==6){
                    employee.set_last_name(list[0].simplified());
                    employee.set_first_name(list[1].simplified());
                    employee.set_patronymic(list[2].simplified());
                    employee.set_cabinet(list[3].simplified());
                    employee.set_title(list[4].simplified());
                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
                    int i=0;
                    for(auto item:employee.get_employee()){
                        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i, new QTableWidgetItem(item));
                        i++;
                    }
                }
                data_base.push_back(employee);
            }
            file.close();
            ui->statusBar->showMessage("Записи из файла добавлены");
            file_ = file_name;
            setWindowTitle(file_ + " – " + program_name);
        } else ui->statusBar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");
    } else ui->statusBar->showMessage("Файл '" + file_name + "' не существует");
}

void MainWindow::on_action_Save_triggered()
{
    if (file_ == "") {
        MainWindow::on_action_SaveAs_triggered();
        return;
    }
    QFile file(file_);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        int len = ui->tableWidget->rowCount();
        for (int i = 0; i < len; ++i) {
            for(int j=0; j<5;++j) out<< ui->tableWidget->item(i,j)->text()<<";";
            out<<'\n';
        }
        file.close();
        ui->statusBar->showMessage("Файл записан");
        setWindowTitle(file_ + " – " + program_name);
    }
}

void MainWindow::on_action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    if (file_name != "") {
        if(file_name.indexOf(".csv")==-1){
            file_name+=".csv";
        }
        file_ = file_name;
        MainWindow::on_action_Save_triggered();
    }
}

void MainWindow::on_action_Merge_triggered()
{
    QString old_file = file_;
    MainWindow::on_action_Open_triggered(false);
    file_ = old_file;
    ui->statusBar->showMessage("Данные объединены");
    setWindowTitle("*" + file_ + " – " + program_name);
}

void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::on_action_Edit_triggered();
}

void MainWindow::on_action_ShowData_triggered()
{
    Show_Data myDialog;
    QString answer;
    if(!data_base.isEmpty()){
        for (Employee employee : data_base) {
            for(auto item:employee.get_employee()){
                answer+=item+";";
            }
            answer+='\n';
        }
    }
    myDialog.setText(answer);
    myDialog.exec();
}
