#include "pf_spike.h"

PF_spike::PF_spike(int px,int py,QWidget *mw)
{
    x=px;
    y=py;
    p=new QLabel(mw);
    p->setPixmap(QPixmap(":/Source/Pf_Spike.png"));
    p->setGeometry(x,y,120,20);
    p->show();
    P1_Used=0;
    P2_Used=0;
    step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_spike.wav"));
}

void PF_spike::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0){return;}
    if(player==1&&P1_Used==0){
        step_sound.play();
        HP-=64;
        P1_Used=1;
        p->setPixmap(QPixmap(":/Source/Pf_Spike_Blood.png"));
        Chara->Reset();
    }
    if(player==2&&P2_Used==0){
        step_sound.play();
        HP-=64;
        P2_Used=1;
        p->setPixmap(QPixmap(":/Source/Pf_Spike_Blood.png"));
        Chara->Reset();
    }
}

void PF_spike::paint(){
    p->move(x,y-10);
}
