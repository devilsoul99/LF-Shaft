#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(GameLoop()));
    timer->start(50);
    srand(time(NULL));

    //------------------------------------------------音效和背景音樂
    QString path = QApplication::applicationDirPath();
    QMediaPlaylist* List1 = new QMediaPlaylist;
    List1->addMedia(QUrl::fromLocalFile(path+"/Sound/stage1.mp3"));
    List1->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlaylist* List2 = new QMediaPlaylist;
    List2->addMedia(QUrl::fromLocalFile(path+"/Sound/stage2.mp3"));
    List2->setPlaybackMode(QMediaPlaylist::Loop);
    bgm.setPlaylist(List1);
    bgm.setVolume(60);

    gameover_sound.setMedia(QUrl::fromLocalFile(path+"/Sound/game_over.wav"));
    death_sound.setMedia(QUrl::fromLocalFile(path+"/Sound/Death.wav"));
    spiked_sound.setMedia(QUrl::fromLocalFile(path+"/Sound/step_spike.wav"));

    //-------------------------------------------------
    HP1=0;MP1=0;
    HP2=0;MP2=0;
    GameMode=0;
    Time=0;
    speed=4;
    stage=0;
    Pause=0;
    Mute=0;
    Difficulty=3;
    bgm_track=0;
    p1_record=0;
    p2_record=0;
    this->GameReset();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::SetGameMode(int gm,int p1c,int p2c){
    GameMode=gm;
    press_right=0;
    press_left=0;
    press_c=0;
    press_z=0;
    p1_dead=0;
    p2_dead=0;
    p1=p1c;
    p2=p2c;
    ui->HP_Bar1->move(597,25);
    ui->MP_Bar1->move(597,53);
    HP1=160;
    MP1=160;
    HP2=160;
    MP2=160;
    if(GameMode==2){
        ui->HP_Bar2->move(597,104);
        ui->MP_Bar2->move(597,133);
    }
    Char1 = new Character;
    Char2 = new Character;
    Char1->setChara(p1,this);
    ui->P1_s->setPixmap(QPixmap(":/Source/"+QString::number(p1,10)+"_s.bmp"));
    if(GameMode==2){
        Char2->setChara(p2,this);
        ui->P2_s->setPixmap(QPixmap(":/Source/"+QString::number(p2,10)+"_s.bmp"));
    }
    P_Vector[3]->bye();
    P_Vector[3]=new PF_normal(200,400,this);
    p1_step_on=1;
    p2_step_on=1;
    if(GameMode==1){
        Char1->set_pos( (P_Vector[3]->getX())+20,(P_Vector[3]->getY())-70   );
        ui->P1_s->move(535,22);
    }
    if(GameMode==2){
        Char1->set_pos( P_Vector[3]->getX()+60,(P_Vector[3]->getY())-70   );
        Char2->set_pos( (P_Vector[3]->getX()),(P_Vector[3]->getY())-70   );
        ui->P1_s->move(535,22);
        ui->P2_s->move(535,102);
    }
    p1_state=0;
    p1_state_tmp=0;
    p1_step_on=0;
    p1_step_on_tmp=0;
    p1_step_on_time=0;
    p2_state=0;
    p2_state_tmp=0;
    p2_step_on=0;
    p2_step_on_tmp=0;
    p2_step_on_time=0;
    bgm.play();
    return;

}

void MainWindow::GameLoop(){
    if(Pause==1){return;}//暫停狀態下跳過此迴圈

    if(stage==150&&bgm_track==0){//到150階換BGM
        QString path = QApplication::applicationDirPath();
        QMediaPlaylist* List2 = new QMediaPlaylist;
        List2->addMedia(QUrl::fromLocalFile(path+"/Sound/stage2.mp3"));
        List2->setPlaybackMode(QMediaPlaylist::Loop);
        bgm.setPlaylist(List2);
        if(Mute==0){bgm.play();}
        bgm_track=1;
    }

    unsigned int i;
    if(GameMode!=0){//判斷P1是否站在台階上
        for(i=0;i<P_Vector.size();++i){
            if(P_Vector[i]->Check_on(1,Char1->getX(),Char1->getY(),Gravity_1)==true){
                p1_step_on=1;
                Char1->set_pos(Char1->getX(),P_Vector[i]->getY()-72);
                Char1->ResetGravity();
                if(p1_dead==0&&p1_step_on_tmp==0){p1_step_on_tmp=1;p1_step_on_time=4;}
                P_Vector[i]->Step(1,Char1,HP1);//執行對應平台效果
                break;
            }
            else{
                p1_step_on=0;
                if(p1_dead==0&&p1_step_on_tmp==0){p1_step_on_tmp=0;p1_step_on_time=0;}
            }
        }
    }
    if(GameMode==2){//判斷P2是否站在台階上
        for(i=0;i<P_Vector.size();++i){
            if(P_Vector[i]->Check_on(2,Char2->getX(),Char2->getY(),Gravity_2)==true){
                p2_step_on=1;
                Char2->ResetGravity();
                Char2->set_pos(Char2->getX(),P_Vector[i]->getY()-72);
                if(p2_dead==0&&p2_step_on_tmp==0){p2_step_on_tmp=1;;p2_step_on_time=4;}
                P_Vector[i]->Step(2,Char2,HP2);//執行對應平台效果
                break;
            }
            else{
                p2_step_on=0;
                if(p2_dead==0&&p2_step_on_tmp==0){p2_step_on_tmp=0;p2_step_on_time=0;}
            }
        }
    }

    for(i=0;i<P_Vector.size();++i){
        P_Vector[i]->go_up(speed);
    }
    if(GameMode!=0&&p1_step_on==0){
        Gravity_1=(Char1->fall());
    }
    if(GameMode==2&&p2_step_on==0){
        Gravity_2=(Char2->fall());
    }

    if(P_Vector.size()>=1&&(P_Vector[0]->getY())<=20){//將最上面的平台清除
        P_Vector[0]->bye();
        P_Vector.erase(P_Vector.begin());
        if(GameMode!=0){
            stage++;
            ui->lcdNumber_stage->display(stage);
        }
    }


    if(GameMode!=0&&p1_state==0){//P1向右站
        if(p1_state_tmp!=p1_state&&p1_dead==0){
            Char1->Reset();
            p1_state_tmp=p1_state;
        }
        if(p1_step_on_time>0&&p1_step_on==1){
            Char1->StepR();
            p1_step_on_time--;
        }
        else{
            Char1->StandR(p1_step_on);
        }
    }
    if(GameMode==2&&p2_state==0){//P2向右站
        if(p2_state_tmp!=p2_state&&p2_dead==0){
            Char2->Reset();
            p2_state_tmp=p2_state;
        }
        if(p2_step_on_time>0&&p2_step_on==1){
            Char2->StepR();
            p2_step_on_time--;
        }
        else{
            Char2->StandR(p2_step_on);
        }
    }
    if(GameMode!=0&&p1_state==1){//P1向左站
        if(p1_state_tmp!=p1_state&&p1_dead==0){
            Char1->Reset();
            p1_state_tmp=p1_state;
        }
        if(p1_step_on_time>0&&p1_step_on==1){
            Char1->StepL();
            p1_step_on_time--;
        }
        else{
            Char1->StandL(p1_step_on);
        }
    }
    if(GameMode==2&&p2_state==1){//P2向左站
        if(p2_state_tmp!=p2_state&&p2_dead==0){
            Char2->Reset();
            p2_state_tmp=p2_state;
        }
        if(p2_step_on_time>0&&p2_step_on==1){
            Char2->StepL();
            p2_step_on_time--;
        }
        else{
            Char2->StandL(p2_step_on);
        }
    }
    if(GameMode!=0&&p1_state==2){//P1向右走
        if(p1_step_on==1){p1_step_on_tmp=1;}
        else{p1_step_on_tmp=0;}
        p1_step_on_time=0;
        if(p1_state_tmp!=p1_state&&p1_dead==0){
            Char1->Reset();
            p1_state_tmp=p1_state;
        }
        Char1->WalkR(p1_step_on);
    }
    if(GameMode==2&&p2_state==2){//P2向右走
        if(p2_step_on==1){p2_step_on_tmp=1;}
        else{p2_step_on_tmp=0;}
        p2_step_on_time=0;
        if(p2_state_tmp!=p2_state&&p2_dead==0){
            Char2->Reset();
            p2_state_tmp=p2_state;
        }
        Char2->WalkR(p2_step_on);
    }
    if(GameMode!=0&&p1_state==3){//P1向左走
        if(p1_step_on==1){p1_step_on_tmp=1;}
        else{p1_step_on_tmp=0;}
        p1_step_on_time=0;
        if(p1_state_tmp!=p1_state&&p1_dead==0){
            Char1->Reset();
            p1_state_tmp=p1_state;
        }
        Char1->WalkL(p1_step_on);
    }
    if(GameMode==2&&p2_state==3){//P2向左走
        if(p2_step_on==1){p2_step_on_tmp=1;}
        else{p2_step_on_tmp=0;}
        p2_step_on_time=0;
        if(p2_state_tmp!=p2_state&&p2_dead==0){
            Char2->Reset();
            p2_state_tmp=p2_state;
        }
        Char2->WalkL(p2_step_on);
    }

    if(GameMode!=0){
        if(Char1->getY()<-5){//P1觸碰頂端
            if(p1_dead==0){
                spiked_sound.play();
                HP1-=64;
                Char1->set_pos(Char1->getX(),15);
                p1_step_on_tmp=0;p1_step_on_time=0;
                *Char1+=0;

            }
            else{
                if(Char1->getY()<-15){Char1->set_pos(999,999);}
            }
        }
        if(Char2->getY()<-5){//P2觸碰頂端
            if(p2_dead==0){
                spiked_sound.play();
                HP2-=64;
                Char2->set_pos(Char2->getX(),15);
                p2_step_on_tmp=0;p2_step_on_time=0;
                *Char2+=0;
            }
            else{
                if(Char2->getY()<-15){Char2->set_pos(999,999);}
            }
        }
        if(Char1->getY()>610){//p1掉落到底部
            HP1=0;MP1=0;
            Char1->set_pos(999,999);
        }
        if(Char2->getY()>610){//p2掉落到底部
            HP2=0;MP2=0;
            Char2->set_pos(999,999);
        }
    }
    if(GameMode!=0){//有人死亡
        if(HP1<=0&&p1_dead==0){//P1掛點
            death_sound.play();
            ui->HP_Bar1->move(999,999);
            ui->MP_Bar1->move(999,999);
            p1_record=stage;
            ui->label_P1->setText("P1: "+QString::number(p1_record,10));
            ui->label_P1->move(530,410);
            p1_dead=1;
            Char1->Reset();
            Char1->Dead();
            if(p1_state==2){p1_state=0;}
            if(p1_state==3){p1_state=1;}

        }
        if(GameMode==2&&HP2<=0&&p2_dead==0){//P2掛點
            death_sound.play();
            ui->HP_Bar2->move(999,999);
            ui->MP_Bar2->move(999,999);
            p2_record=stage;
            ui->label_P2->setText("P2: "+QString::number(p2_record,10));
            ui->label_P2->move(530,450);
            p2_dead=1;
            Char2->Reset();
            Char2->Dead();
            if(p2_state==2){p2_state=0;}
            if(p2_state==3){p2_state=1;}
        }
    }

    if(GameMode!=0&&Time>0&&Time%600==0&&speed<7){//30秒加速一次 調整難度
        speed++;Difficulty+=2;
    }

    if(GameMode!=0){//顯示秒數
        ui->lcdNumber_time->display(Time/20);
        Time++;
    }

    //即時更新HP MP
    ui->HP_Bar1->setFixedWidth(HP1);
    ui->MP_Bar1->setFixedWidth(MP1);
    if(GameMode==2){
        ui->HP_Bar2->setFixedWidth(HP2);
        ui->MP_Bar2->setFixedWidth(MP2);
    }


    if(P_Vector.size()<2){//至少有兩個平台
        Platform *pf = get_platform();
        P_Vector.push_back(pf);
    }
    else if(rand()%Difficulty==0&&P_Vector[(P_Vector.size()-1)]->getY()<550){//新增平台

        Platform *pf = get_platform();
        P_Vector.push_back(pf);
    }

    if(GameMode==1&&p1_dead==1&&Char1->getX()==999){//單人模式遊戲結束
        bgm.stop();
        gameover_sound.play();
        ui->label_Gameover->move(0,280);
        p2_dead=1;
        p2_record=0;
        GameMode=0;
        delete Char1;
    }
    if(GameMode==2&&p1_dead==1&&p2_dead==1&&Char1->getX()==999&&Char2->getX()==999){//2人模式遊戲結束
        bgm.stop();
        gameover_sound.play();
        ui->label_Gameover->move(0,280);
        GameMode=0;
        delete Char1;
        delete Char2;
    }


}

void MainWindow::keyPressEvent(QKeyEvent *in){
    if(GameMode!=0&&p1_dead==0&&in->key()==Qt::Key_Right){
        p1_state=2;press_right=1;
    }
    if(GameMode!=0&&p1_dead==0&&in->key()==Qt::Key_Left){
        p1_state=3;press_left=1;
    }
    if(GameMode==2&&p2_dead==0&&in->key()==Qt::Key_C){
        p2_state=2;press_c=1;
    }
    if(GameMode==2&&p2_dead==0&&in->key()==Qt::Key_Z){
        p2_state=3;press_z=1;
    }
    if(GameMode!=0&&in->key()==Qt::Key_P){//遊戲暫停
        if(Pause==0){
            Pause=1;
            ui->label_Pause->setText("RESUME: P");
        }
        else{
            Pause=0;
            ui->label_Pause->setText("PAUSE: P");
        }
    }
    if(GameMode!=0&&in->key()==Qt::Key_M){//背景靜音
        if(Mute==0){
            Mute=1;
            bgm.stop();
        }
        else{
            bgm.play();
            Mute=0;
        }
    }
    if(GameMode==0&&p1_dead==1&&p2_dead==1&&in->key()==Qt::Key_Space){//遊戲結束
        if(p1_record!=0&&CheckHigh(p1_record)==true){
            EnterName en(p1_record,p1,this);
            en.show();
            en.exec();
        }
        if(p2_record!=0&&CheckHigh(p2_record)==true){
            EnterName en(p2_record,p2,this);
            en.show();
            en.exec();
        }
        ui->label_Gameover->move(999,999);
        ui->P1_s->move(999,999);
        ui->P2_s->move(999,999);
        this->GameReset();
        emit OpenIntro();
    }
}

bool MainWindow::CheckHigh(int rc){
    checkf:
    std::ifstream inFile("ScoreBoard.sb", std::ios::in);
    if(!inFile){
        std::ofstream outFile("ScoreBoard.sb", std::ios::out);
        outFile<<"Stage\tChar\tLenth\tName\n";
        outFile.close();
        goto checkf;
    }
    std::string trash;
    getline(inFile,trash);
    unsigned int i;
    int compare=0;
    for(i=0;i<10;i++){
        inFile>>compare;
        getline(inFile,trash);
        if(rc>compare||compare==-1){return true;}
        compare=-1;
    }
    return false;
}

void MainWindow::keyReleaseEvent(QKeyEvent *in){
    if(GameMode!=0&&p1_dead==0&&in->key()==Qt::Key_Right){
        p1_state=0;press_right=0;
        if(press_left==1){p1_state=3;}
    }
    if(GameMode!=0&&p1_dead==0&&in->key()==Qt::Key_Left){
        p1_state=1;press_left=0;
        if(press_right==1){p1_state=2;}
    }
    if(GameMode==2&&p2_dead==0&&in->key()==Qt::Key_C){
        p2_state=0;press_c=0;
        if(press_z==1){p2_state=3;}
    }
    if(GameMode==2&&p2_dead==0&&in->key()==Qt::Key_Z){
        p2_state=1;press_z=0;
        if(press_c==1){p2_state=2;}
    }

}

Platform* MainWindow::get_platform(){//隨機獲取新的平台
    int randnewpf=rand()%12;
    Platform *newpf;
    switch(randnewpf){
        case 1:{
            newpf = new PF_spike(rand()%401,630,this);
            break;
        }
        case 2:{
            newpf = new PF_flip(rand()%401,630,this);
            break;
        }
        case 3:{
            newpf = new PF_left(rand()%401,630,this);
            break;
        }
        case 4:{
            newpf = new PF_right(rand()%401,630,this);
            break;
        }
        case 5:{
            newpf = new PF_spike(rand()%401,630,this);
            break;
        }
        case 6:{
            newpf = new PF_string(rand()%401,630,this);
            break;
        }
        case 7:{
            newpf = new PF_ufox((rand()%281)+60,630,this);
            break;
        }
        case 8:{
            newpf = new PF_ufoy(rand()%401,630,this);
            break;
        }
        default:{
            newpf = new PF_normal(rand()%401,630,this);
            break;
        }
    }
    return newpf;
}

void MainWindow::GameReset(){//遊戲視窗 資料初始化
    GameMode=0;
    Time=0;
    speed=4;
    stage=0;
    Pause=0;
    Mute=0;
    ui->HP_Bar1->move(999,999);
    ui->HP_Bar2->move(999,999);
    ui->MP_Bar1->move(999,999);
    ui->MP_Bar2->move(999,999);
    ui->label_P1->move(999,999);
    ui->label_P2->move(999,999);
    Difficulty=3;
    bgm_track=0;
    Gravity_1=0;
    Gravity_2=0;
    unsigned int i,wp;
    if(P_Vector.size()>=1){//清空VECTOR
        for(i=0;i<P_Vector.size();i++){
            P_Vector[i]->bye();
        }
        P_Vector.clear();
    }
    Platform *pf;
    for(i=0;i<5;i++){
        wp=rand()%6;
        switch(wp){
            case 1:{
                pf = new PF_spike(rand()%401,(600/5)*i,this);
                break;
            }
            case 2:{
                pf = new PF_flip(rand()%401,(600/5)*i,this);
                break;
            }
            case 3:{
                pf = new PF_left(rand()%401,(600/5)*i,this);
                break;
            }
            case 4:{
                pf = new PF_right(rand()%401,(600/5)*i,this);
                break;
            }
            default:{
                pf = new PF_normal(rand()%401,(600/5)*i,this);
                break;
            }
        }
        P_Vector.push_back(pf);
    }
    return;
}
