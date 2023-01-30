#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QDialog>

namespace Ui {
    class Show_Data;
}

class Show_Data : public QDialog
{
    Q_OBJECT

public:
    explicit Show_Data(QWidget *parent = nullptr);
    void setText(const QString &str);
    QString getText();
    ~Show_Data();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Show_Data *ui;
};

#endif // SHOWDATA_H
