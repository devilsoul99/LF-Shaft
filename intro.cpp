#include "intro.h"
#include "ui_intro.h"

Intro::Intro(MainWindow *mw,QWidget *parent) :
    QDialog(parent),ui(new Ui::Intro),p1(2),p2(1)
{
    ui->setupUi(this);
    w=mw;
    ui->p1_pic->setPixmap(QPixmap(":/Source/"+QString::number(p1,10)+"_f.bmp"));
    ui->p2_pic->setPixmap(QPixmap(":/Source/"+QString::number(p2,10)+"_f.bmp"));
    QObject::connect(w,SIGNAL(OpenIntro()),this,SLOT(ReOpen()));
    swap_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/menu_switch.wav"));
    ok_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/menu_ok.wav"));
}
Intro::~Intro(){
    delete ui;
}
void Intro::ReOpen(){
    this->setVisible(true);
}
void Intro::keyPressEvent(QKeyEvent *in){
    if(in->key()==Qt::Key_Left){
        swap_sound.play();
        p1--;
        if(p1<0){p1=8;}
        ui->p1_pic->setPixmap(QPixmap(":/Source/"+QString::number(p1,10)+"_f.bmp"));
    }
    if(in->key()==Qt::Key_Right){
        swap_sound.play();
        p1++;
        if(p1>8){p1=0;}
        ui->p1_pic->setPixmap(QPixmap(":/Source/"+QString::number(p1,10)+"_f.bmp"));
    }
    if(in->key()==Qt::Key_Z){
        swap_sound.play();
        p2--;
        if(p2<0){p2=8;}
        ui->p2_pic->setPixmap(QPixmap(":/Source/"+QString::number(p2,10)+"_f.bmp"));
    }
    if(in->key()==Qt::Key_C){
        swap_sound.play();
        p2++;
        if(p2>8){p2=0;}
        ui->p2_pic->setPixmap(QPixmap(":/Source/"+QString::number(p2,10)+"_f.bmp"));
    }
    if(in->key()==Qt::Key_Up||in->key()==Qt::Key_S){
        swap_sound.play();
        if(ui->CHOICE->y()<=260){ui->CHOICE->move(150,335);}
        else{ui->CHOICE->move(150,ui->CHOICE->y()-25);}
    }
    if(in->key()==Qt::Key_Down||in->key()==Qt::Key_X){
        swap_sound.play();
        if(ui->CHOICE->y()>=335){ui->CHOICE->move(150,260);}
        else{ui->CHOICE->move(150,ui->CHOICE->y()+25);}
    }
    if(in->key()==Qt::Key_Space){
        if(ui->CHOICE->y()>=335){exit(0);}
        if(ui->CHOICE->y()==260){
            ok_sound.play();
            w->SetGameMode(1,p1,p2);
            this->setVisible(false);
        }
        if(ui->CHOICE->y()==285){
            ok_sound.play();
            w->SetGameMode(2,p1,p2);
            this->setVisible(false);
        }
        if(ui->CHOICE->y()==310){
            ok_sound.play();
            ShowHigh sw;
            sw.show();
            sw.exec();
        }
    }
}
