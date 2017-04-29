#include "pf_right.h"

PF_right::PF_right(int px,int py,QWidget *mw)
{
    x=px;
    y=py;
    frame=0;
    p=new QLabel(mw);
    p->setPixmap(QPixmap(":/Source/Pf_Move.png").copy(0,0,120,20));
    p->setGeometry(x,y,120,20);
    p->show();
    P1_Used=0;
    P2_Used=0;
    step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_move.wav"));
}

void PF_right::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0){return;}
    if(Chara->getX()<470){
        Chara->set_pos(Chara->getX()+8,Chara->getY());
    }
    if(player==1&&P1_Used==0){
        step_sound.play();
        HP+=16;
        P1_Used=1;
        Chara->Reset();
    }
    if(player==2&&P2_Used==0){
        step_sound.play();
        HP+=16;
        P2_Used=1;
        Chara->Reset();
    }
    if(HP>160){
        HP=160;
    }

}

void PF_right::paint(){
    frame++;
    if(frame>=8){frame=0;}
    p->setPixmap(QPixmap(":/Source/Pf_Move.png").copy(0,20*frame,120,20));
    p->move(x,y);

}
