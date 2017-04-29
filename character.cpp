#include "character.h"

Character::Character(QWidget *parent) :
    QObject(parent){
    type=0;
    x=0;y=0;
    state=0;
    TimeCheck=0;
    FrameBack=0;
    Gravity=5;
    dead=0;
    bounce=0;
    bounceTime=0;


}
void Character::setChara(int a,QWidget *mw){
    type=a;
    Pic=new QLabel(mw);
    Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0,0,60,60));

    Pic->show();
    state=0;
    TimeCheck=0;
    FrameBack=0;
    Gravity=5;
    dead=0;
    bounce=0;

}

void Character::set_pos(int a,int b){
    x=a;
    y=b;
    Pic->setGeometry(x,y,80,80);
}

void Character::StandR(int stand){
    TimeCheck++;
    if(dead==1){
        if(state>=5){
            Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(240,240,60,60));
        }
        else{
            Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0+(state*60),240,60,60));
        }
        if(TimeCheck>0&&TimeCheck%2==0){state++;}
        return;
    }

    if(bounce==1){//起跳動作
        TimeCheck++;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0+(state*60),360,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>1){
            state=0;
        }
        return;
    }
    if(bounce>=2){//跳躍
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(120,360,60,60));
        y=y-(52-(bounce*4));
        bounce++;
        if(bounce>12){bounce=0;}
        return;
    }

    if(stand==1){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0+(state*60),0,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>3){
            state=0;
        }
    }
    if(stand==0){
        state=0;
        TimeCheck=0;
        FrameBack=0;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(120,360,60,60));
    }
}

void Character::StandL(int stand){
    TimeCheck++;
    if(dead==1){
        if(state>=5){
            Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(300,240,60,60));
        }
        else{
            Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(540-(state*60),240,60,60));
        }
        if(TimeCheck>0&&TimeCheck%2==0){state++;}
        return;
    }
    if(bounce==1){//起跳動作
        TimeCheck++;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(540-(state*60),360,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>1){
            state=0;
        }
        return;
    }
    if(bounce>=2){//跳躍
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(420,360,60,60));
        y=y-(52-(bounce*4));
        bounce++;
        if(bounce>12){bounce=0;}
        return;
    }


    if(stand==1){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(540-(state*60),0,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>3){
            state=0;
        }
    }
    if(stand==0){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(420,360,60,60));
        state=0;
        TimeCheck=0;
        FrameBack=0;
    }
}

void Character::WalkR(int stand){
    TimeCheck++;
    if(bounce!=1&&x<470){
        x+=13;
        Pic->move(x,y);
    }
    if(bounce==1){//起跳動作
        TimeCheck++;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0+(state*60),360,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>1){
            state=0;
        }
        return;
    }
    if(bounce>=2){//跳躍
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(120,360,60,60));
        y=y-(52-(bounce*4));
        bounce++;
        if(bounce>12){bounce=0;}
        return;
    }
    if(stand==1){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(240+(state*60),0,60,60));
        if(TimeCheck==1&&FrameBack==0){state++;TimeCheck=0;}
        if(TimeCheck==1&&FrameBack==1){state--;TimeCheck=0;}
        if(state>3){
            state=2;
            FrameBack=1;
        }
        if(state<0){
            state=1;
            FrameBack=0;
        }
    }
    if(stand==0){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(120,360,60,60));
        state=0;
        TimeCheck=0;
        FrameBack=0;
    }
}

void Character::WalkL(int stand){
    TimeCheck++;
    if(bounce!=1&&x>-10){
        x-=13;
        Pic->move(x,y);
    }
    if(bounce==1){//起跳動作
        TimeCheck++;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(540-(state*60),360,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>1){
            state=0;
        }
        return;
    }
    if(bounce>=2){//跳躍
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(420,360,60,60));
        y=y-(52-(bounce*4));
        bounce++;
        if(bounce>12){bounce=0;}
        return;
    }

    if(stand==1){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(300-(state*60),0,60,60));
        if(TimeCheck==1&&FrameBack==0){state++;TimeCheck=0;}
        if(TimeCheck==1&&FrameBack==1){state--;TimeCheck=0;}
        if(state>3){
            state=2;
            FrameBack=1;
        }
        if(state<0){
            state=1;
            FrameBack=0;
        }
    }
    if(stand==0){
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(420,360,60,60));
        state=0;
        TimeCheck=0;
        FrameBack=0;
    }
}

void Character::StepR(){
    TimeCheck++;

    if(bounce==1){//起跳動作
        TimeCheck++;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0+(state*60),360,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>1){
            state=0;
        }
        return;
    }
    if(bounce>=2){//跳躍
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(120,360,60,60));
        y=y-(52-(bounce*4));
        bounce++;
        if(bounce>12){bounce=0;}
        return;
    }

    Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_right.png").copy(0+(state*60),360,60,60));
    if(TimeCheck==2){state++;TimeCheck=0;}
    if(state>1){
        state=0;
    }

}
void Character::StepL(){
    TimeCheck++;

    if(bounce==1){//起跳動作
        TimeCheck++;
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(540-(state*60),360,60,60));
        if(TimeCheck==2){state++;TimeCheck=0;}
        if(state>1){
            state=0;
        }
        return;
    }
    if(bounce>=2){//跳躍
        Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(420,360,60,60));
        y=y-(52-(bounce*4));
        bounce++;
        if(bounce>12){bounce=0;}
        return;
    }

    Pic->setPixmap(QPixmap(":/Source/"+QString::number(type,10)+"_left.png").copy(540-(state*60),360,60,60));
    if(TimeCheck==2){state++;TimeCheck=0;}
    if(state>1){
        state=0;
    }
}

void Character::Dead(){
    dead=1;
    return;
}

void Character::Reset(){
    state=0;
    TimeCheck=0;
    FrameBack=0;
    if(bounce<2){bounce=0;}
}
void Character::ResetGravity(){
    Gravity=5;
}

int Character::getX(){
    return x;
}
int Character::getY(){
    return y;
}
double Character::fall(){
    y=y+Gravity;
    Pic->move(x,y);
    Gravity+=2;
    this->Reset();
    return Gravity;
}

void Character::setFlip(){
    Pic->raise();
    return;
}

void Character::operator+=(int a){
    bounce=a;
    return;
}

int Character::getBounce(){
    return bounce;
}

