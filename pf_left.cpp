#include "pf_left.h"

PF_left::PF_left(int px,int py,QWidget *mw)
{
    x=px;
    y=py;
    frame=0;
    p=new QLabel(mw);
    p->setPixmap(QPixmap(":/Source/Pf_Move.png").copy(120,0,120,20));
    p->setGeometry(x,y,120,20);
    p->show();
    P1_Used=0;
    P2_Used=0;
    step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_move.wav"));
}

void PF_left::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0){return;}
    if(Chara->getX()>-10){
        Chara->set_pos(Chara->getX()-8,Chara->getY());
    }
    if(player==1&&P1_Used==0){
        step_sound.play();
        Chara->Reset();
        HP+=16;
        P1_Used=1;
    }
    if(player==2&&P2_Used==0){
        step_sound.play();
        Chara->Reset();
        HP+=16;
        P2_Used=1;
    }
    if(HP>160){
        HP=160;
    }
}

void PF_left::paint(){
    frame++;
    if(frame>=8){frame=0;}
    p->setPixmap(QPixmap(":/Source/Pf_Move.png").copy(120,20*frame,120,20));
    p->move(x,y);

}
