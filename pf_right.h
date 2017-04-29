#ifndef PF_RIGHT_H
#define PF_RIGHT_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QSound>

class PF_right : public Platform
{
    Q_OBJECT
public:
    PF_right(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();

private:

    int frame;

};


#endif // PF_RIGHT_H
