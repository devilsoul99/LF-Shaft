#ifndef INTRO_H
#define INTRO_H

#include <QDialog>
#include <QString>
#include <QPixmap>
#include <QKeyEvent>
#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include "showhigh.h"

namespace Ui {
class Intro;
}
class Intro : public QDialog
{
    Q_OBJECT
public:
    explicit Intro(MainWindow *,QWidget *parent = 0);
    ~Intro();
private slots:

public slots:
    void ReOpen();
protected:
    void keyPressEvent(QKeyEvent*);
private:
    Ui::Intro *ui;
    MainWindow *w;
    QMediaPlayer swap_sound,ok_sound;
    int p1;
    int p2;
};
#endif // INTRO_H
