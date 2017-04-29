#ifndef ENTERNAME_H
#define ENTERNAME_H

#include <QDialog>
#include <fstream>
#include <iostream>
#include <QString>
#include <string>


namespace Ui {
class EnterName;
}

class EnterName : public QDialog
{
    Q_OBJECT
public:
    explicit EnterName(int,int,QWidget *parent = 0);
    ~EnterName();
private slots:
    void on_pushButton_OK_clicked();
    void on_pushButton_Cancel_clicked();

private:
    Ui::EnterName *ui;
    int record_stage;
    int character;
};

#endif // ENTERNAME_H
