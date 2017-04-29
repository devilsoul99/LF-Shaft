#include "pf_flip.h"

PF_flip::PF_flip(int px,int py,QWidget *mw)

{
    x=px;
    y=py;
    frame=-4;
    p=new QLabel(mw);
    p->setPixmap(QPixmap(":/Source/Pf_Flip.png").copy(0,0,118,45));
    p->setGeometry(x,y,120,60);
    p->show();
    P1_Used=0;
    P2_Used=0;
    step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/step_flip.wav"));
}

void PF_flip::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0){return;}
    if(frame>=2){
        Chara->setFlip();
        Chara->fall();
        Chara->set_pos(Chara->getX(),Chara->getY()+7);
    }
    if(player==1&&P1_Used==0){
        HP+=16;
        Chara->Reset();
        P1_Used=1;
        step_sound.play();
    }
    if(player==2&&P2_Used==0){
        HP+=16;
        Chara->Reset();
        P2_Used=1;
        step_sound.play();
    }
    if(HP>160){
        HP=160;
    }
}

void PF_flip::paint(){
    if(P1_Used==1||P2_Used==1||frame>0){
        frame++;
        if(frame<6&&frame>0){
            p->setPixmap(QPixmap(":/Source/Pf_Flip.png").copy(0,frame*48,118,45));
        }
        else if(frame>=6){
            p->setPixmap(QPixmap(":/Source/Pf_Flip.png").copy(120,(frame-6)*48,118,45));
        }
        else{
            p->setPixmap(QPixmap(":/Source/Pf_Flip.png").copy(0,0,118,50));
        }
        if(frame==11){
            frame=-4;
            P1_Used=0;
            P2_Used=0;
            p->setPixmap(QPixmap(":/Source/Pf_Flip.png").copy(0,0,118,50));
        }
    }

    p->move(x,y-18);

}
