#ifndef PF_SPIKE_H
#define PF_SPIKE_H

#include "platform.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class PF_spike : public Platform
{
    Q_OBJECT
public:
    PF_spike(int,int,QWidget *);
    virtual void Step(int,Character*,int&);
    virtual void paint();

};

#endif // PF_SPIKE_H
