#include "pf_normal.h"


PF_normal::PF_normal(int px,int py,QWidget *mw)
{
   x=px;
   y=py;
   p=new QLabel(mw);
   p->setPixmap(QPixmap(":/Source/Pf_Normal.PNG"));
   p->setGeometry(x,y,120,20);
   p->show();
   P1_Used=0;
   P2_Used=0;
   step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_normal1.wav"));
   step_sound2.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_normal2.wav"));
}

void PF_normal::paint(){
    p->move(x,y);
}

void PF_normal::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0){return;}
    if(player==1&&P1_Used==0){
        if(x%2==1){
            step_sound.play();
        }
        else{
            step_sound2.play();
        }
        HP+=16;
        P1_Used=1;
        Chara->Reset();
    }
    if(player==2&&P2_Used==0){
        if(x%2==1){
            step_sound2.play();
        }
        else{
            step_sound.play();
        }
        HP+=16;
        P2_Used=1;
        Chara->Reset();
    }
    if(HP>160){
        HP=160;
    }
}
