#include "platform.h"


Platform::Platform(QObject *parent) :
    QObject(parent){

}
Platform::~Platform(){
    p->move(999,999);
    delete p;
}

void Platform::go_up(int speed){
    y=y-speed;
    picy=picy-speed;
    this->paint();
    return;
}

int Platform::getY(){
    return y;
}
int Platform::getX(){
    return x;
}
void Platform::bye(){
    delete this;
}

bool Platform::Check_on(int player,int px,int py,int speed){
    if(py+70+speed>=y&&py+60<=y&&px+40>x&&px<x+100){
        return true;
    }
    if(player==1){P1_Used=0;}
    else {
        P2_Used=0;
    }
    return false;
}
