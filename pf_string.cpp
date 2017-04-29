#include "pf_string.h"

PF_string::PF_string(int px,int py,QWidget *mw)
{
    x=px;
    y=py;
    picx=x;
    picy=y;
    frame=0;
    p=new QLabel(mw);
    p->setPixmap(QPixmap(":/Source/Pf_Spring.png").copy(0,0,120,40));
    p->setGeometry(picx,picy,120,40);
    p->show();
    P1_Used=0;
    P2_Used=0;
    step_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/string_press.wav"));
    bounce_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/string_bounce.wav"));
}
void PF_string::Step(int player,Character* Chara,int &HP){
    if(Chara->getBounce()!=0&&start==0){return;}
    start=1;
    if(Chara->getBounce()>1){
        *Chara+=0;
    }
    if(P1_Used==0&&player==1){
        HP+=16;P1_Used=1;Chara->Reset();Chara->Reset();
        step_sound.play();
    }
    if(P2_Used==0&&player==2){
        HP+=16;P2_Used=1;Chara->Reset();Chara->Reset();
        step_sound.play();
    }
    if(HP>160){HP=160;}
    if(frame<6&&frame>0){
        *Chara+=1;
    }
    if(frame==6){
        *Chara+=2;
        bounce_sound.play();
    }


}
void PF_string::paint(){
    if(start==1){
        frame++;
        if(frame>=7){
            y-=5;
            p->setPixmap(QPixmap(":/Source/Pf_Spring.png").copy(0,280-((frame-6)*40),120,40));
            p->move(picx,picy);
            if(frame==11){
                frame=0;
                start=0;
                x=picx;
                y=picy;
                P1_Used=0;
                P2_Used=0;
            }
        }
        else{
            y+=4;
            p->setPixmap(QPixmap(":/Source/Pf_Spring.png").copy(0,frame*40,120,40));
            p->move(picx,picy);
        }
    }
    else{
        p->move(x,y);
    }
}
