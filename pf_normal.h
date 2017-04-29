#ifndef PF_NORMAL_H
#define PF_NORMAL_H
#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_normal : public Platform
{
    Q_OBJECT
public:
    PF_normal(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();
private:
    QMediaPlayer step_sound2;

};

#endif // PF_NORMAL_H
