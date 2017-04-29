#include "entername.h"
#include "ui_entername.h"

EnterName::EnterName(int b,int a,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterName)
{
    character=a;
    record_stage=b;
    ui->setupUi(this);
    ui->pic_s->setPixmap(QPixmap(":/Source/"+QString::number(character,10)+"_left.png").copy(540,0,60,60));
    ui->Text_Stage->setText("Your stage: "+QString::number(record_stage,10));
    ui->warning->move(999,999);

}

EnterName::~EnterName(){
    delete ui;
}

void EnterName::on_pushButton_OK_clicked(){
    if(ui->NameBox->text().size()<1){
        ui->warning->move(200,150);
        return;
    }

    checkf:
    std::ifstream inFile("ScoreBoard.sb", std::ios::in);

    if(!inFile){
        std::ofstream outFile("ScoreBoard.sb", std::ios::out);
        outFile<<"Stage\tChar\tLenth\tName\n";
        outFile.close();
        goto checkf;
    }


    int oldRecord[10]={0};
    unsigned int i,putline=0;
    std::string trash;
    std::vector<std::string> afterfile;

    getline(inFile,trash);
    afterfile.push_back(trash);
    for(i=0;i<10;i++){//找尋插入紀錄位置 備份排行榜
        inFile>>oldRecord[i];
        getline(inFile,trash);
        afterfile.push_back((QString::number(oldRecord[i]).toStdString())+trash);
        if(i==0&&record_stage>oldRecord[0]){
            putline=0;
        }
        if(i>0&&record_stage>oldRecord[i]&&record_stage<=oldRecord[i-1]){
            putline=i;
        }
    }//新紀錄會在putline行
    inFile.close();
    trash=(QString::number(record_stage).toStdString())+"\t"+(QString::number(character).toStdString())+"\t"+(QString::number(ui->NameBox->text().size()).toStdString())+"\t"+(ui->NameBox->text().toStdString());
    //新紀錄
    afterfile.insert(afterfile.begin()+putline+1,trash);//新紀錄插入
    std::ofstream outFile("ScoreBoard.sb", std::ios::out);
    for(i=0;i<11;i++){
        outFile<<afterfile[i]<<"\n";
        if(i>0&&oldRecord[i-1]==0){break;}
    }
    outFile.close();
    this->close();
    return;
}

void EnterName::on_pushButton_Cancel_clicked(){
    this->close();
    return;
}
