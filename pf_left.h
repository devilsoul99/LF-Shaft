#ifndef PF_LEFT_H
#define PF_LEFT_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_left : public Platform
{
    Q_OBJECT
public:
    PF_left(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();

private:

    int frame;

};

#endif // PF_LEFT_H
