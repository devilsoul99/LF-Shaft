#ifndef PLATFORM_H
#define PLATFORM_H

#include <QLabel>
#include <QApplication>
#include <QMediaPlayer>
#include "character.h"

class Platform : public QObject
{
    Q_OBJECT
public:
    explicit Platform(QObject *parent = 0);
    virtual void Step(int,Character*,int&)=0;
    virtual ~Platform();
    virtual void paint()=0;
    void go_up(int);
    int getY();
    int getX();
    bool Check_on(int,int,int,int);
    void bye();

protected:
    int x,y;
    int P1_Used;
    int P2_Used;
    int picx,picy;
    QLabel *p;
    QMediaPlayer step_sound;
};

#endif // PLATFORM_H
