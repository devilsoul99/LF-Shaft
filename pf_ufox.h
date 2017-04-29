#ifndef PF_UFOX_H
#define PF_UFOX_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_ufox : public Platform
{
    Q_OBJECT
public:
    PF_ufox(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();
private:
    int movex;
    int back;
    QMediaPlayer step_sound2;
};

#endif // PF_UFOX_H
