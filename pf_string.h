#ifndef PF_STRING_H
#define PF_STRING_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_string : public Platform
{
    Q_OBJECT
public:
    PF_string(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();
private:
    int frame;
    int start;
    QMediaPlayer bounce_sound;
};

#endif // PF_STRING_H
