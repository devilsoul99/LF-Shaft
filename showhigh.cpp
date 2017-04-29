#include "showhigh.h"
#include "ui_showhigh.h"

ShowHigh::ShowHigh(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowHigh)
{
    ui->setupUi(this);
    i=0;
    warnmode=0;
    swap_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/menu_switch.wav"));
    ok_sound.setMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/Sound/menu_ok.wav"));

    for(i=0;i<10;i++){
        Record[i]=0;
        Chara[i]=0;
        Name[i]=" ";
        Tag[i]=NULL;
        Pic[i]=NULL;
    }

    ui->warning->move(999,999);
    ui->empty->move(999,999);

    checkf:
    std::ifstream inFile("ScoreBoard.sb", std::ios::in);
    if(!inFile){
        std::ofstream outFile("ScoreBoard.sb", std::ios::out);
        outFile<<"Stage\tChar\tLenth\tName\n";
        outFile.close();
        goto checkf;
    }
    std::string line;
    getline(inFile,line);
    QFont font=ui->label_2->font();
    font.setPointSize(10);
    font.setBold(true);
    font.setFamily("Tempus Sans ITC");


    i=0;
    while(getline(inFile,line)){
        QString Qline=QString::fromStdString(line);
        Record[i]=Qline.split("\t")[0].toInt();
        Chara[i]=Qline.split("\t")[1].toInt();
        Name[i]=Qline.split("\t")[3];

        Tag[i]=new QLabel(this);
        Tag[i]->setText(QString::number(i+1)+". "+Name[i]+"<br>   Stage: "+QString::number(Record[i]));
        Pic[i]=new QLabel(this);
        Pic[i]->setPixmap(QPixmap(":/Source/"+QString::number(Chara[i])+"_right.png").copy(0,0,60,60));
        if(i+1<6){
            Tag[i]->move(50,30+(70*i));
            Pic[i]->move(-10,20+(70*i));
        }
        else{
            Tag[i]->move(200,30+(70*(i-5)));
            Pic[i]->move(140,20+(70*(i-5)));
        }
        Tag[i]->setFont(font);
        Tag[i]->setStyleSheet("color: rgb(255, 255, 255);");
        Tag[i]->show();
        Pic[i]->show();


        i++;
    }

    if(i==0){
        ui->empty->move(35,180);
        ui->empty->raise();
    }
    inFile.close();
}

ShowHigh::~ShowHigh(){
    delete ui;
}
void ShowHigh::keyPressEvent(QKeyEvent *in){
    if(warnmode==0&&(in->key()==Qt::Key_Up||in->key()==Qt::Key_S)){
        swap_sound.play();
        if(ui->CHOICE->y()==391){ui->CHOICE->move(115,421);}
        else{ui->CHOICE->move(115,391);}
    }
    if(warnmode==0&&(in->key()==Qt::Key_Down||in->key()==Qt::Key_X)){
        swap_sound.play();
        if(ui->CHOICE->y()==391){ui->CHOICE->move(115,421);}
        else{ui->CHOICE->move(115,391);}
    }
    if(warnmode==0&&in->key()==Qt::Key_Space){
        if(ui->CHOICE->y()==391){
            ok_sound.play();
            this->close();
        }
        else{
            ok_sound.play();
            warnmode=1;
            ui->warning->move(0,150);
            ui->warning->raise();
        }
    }
    if(warnmode==1&&in->key()==Qt::Key_Y){
        ok_sound.play();
        warnmode=0;
        ui->warning->move(999,999);
        std::ofstream outFile("ScoreBoard.sb", std::ios::out);
        outFile<<"Stage\tChar\tLenth\tName\n";
        outFile.close();
        this->close();
    }
    if(warnmode==1&&in->key()==Qt::Key_N){
        swap_sound.play();
        warnmode=0;
        ui->warning->move(999,999);
    }
}
