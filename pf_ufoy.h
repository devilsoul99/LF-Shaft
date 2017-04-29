#ifndef PF_UFOY_H
#define PF_UFOY_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_ufoy : public Platform
{
    Q_OBJECT
public:
    PF_ufoy(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();
private:
    int movey;
    int back;
    QMediaPlayer step_sound2;
};

#endif // PF_UFOY_H
