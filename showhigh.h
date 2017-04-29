#ifndef SHOWHIGH_H
#define SHOWHIGH_H

#include <QDialog>
#include <QKeyEvent>
#include <fstream>
#include <iostream>
#include <QString>
#include <string>
#include <QLabel>
#include <QFont>
#include <QApplication>
#include <QMediaPlayer>

namespace Ui {
class ShowHigh;
}

class ShowHigh : public QDialog
{
    Q_OBJECT
public:
    explicit ShowHigh(QWidget *parent = 0);
    ~ShowHigh();
protected:
    void keyPressEvent(QKeyEvent*);
private:
    Ui::ShowHigh *ui;
    int Record[10],Chara[10];
    QString Name[10];
    QLabel *Tag[10];
    QLabel *Pic[10];
    unsigned int i;
    int warnmode;
    QMediaPlayer swap_sound,ok_sound;
};

#endif // SHOWHIGH_H
