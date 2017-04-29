#include "pf_ufox.h"

PF_ufox::PF_ufox(int px,int py,QWidget *mw)
{
   x=px;
   y=py;
   p=new QLabel(mw);
   p->setPixmap(QPixmap(":/Source/Pf_Normal.PNG"));
   p->setGeometry(x,y,120,20);
   p->show();
   P1_Used=0;
   P2_Used=0;
   movex=0;
   back=0;
   step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_normal1.wav"));
   step_sound2.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_normal2.wav"));

}
void PF_ufox::paint(){
    if(movex<=60&&back==0){
        movex+=4;
        x+=4;
        if(movex==60){back=1;}
    }
    if(movex>=-60&&back==1){
        movex-=4;
        x-=4;
        if(movex==-60){back=0;}
    }
    p->move(x,y);
}
void PF_ufox::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0){return;}
    if(movex<=60&&back==0){
        Chara->set_pos(Chara->getX()+4,Chara->getY());
    }
    if(movex>=-60&&back==1){
        Chara->set_pos(Chara->getX()-4,Chara->getY());
    }
    if(player==1&&P1_Used==0){
        if(x%2==1){
            step_sound2.play();
        }
        else{
            step_sound.play();
        }
        HP+=16;
        P1_Used=1;
        Chara->Reset();
    }
    if(player==2&&P2_Used==0){
        if(x%2==1){
            step_sound.play();
        }
        else{
            step_sound2.play();
        }
        HP+=16;
        P2_Used=1;
        Chara->Reset();
    }
    if(HP>160){
        HP=160;
    }
}
