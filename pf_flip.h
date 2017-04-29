#ifndef PF_FLIP_H
#define PF_FLIP_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_flip : public Platform
{
    Q_OBJECT
public:
    PF_flip(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();
private:
    int frame;
};

#endif // PF_FLIP_H
