#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QString>

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(QWidget *parent = 0);
    void setChara(int,QWidget *);
    void set_pos(int,int);
    double fall();
    int getX();
    int getY();
    void StandR(int);
    void StandL(int);
    void WalkR(int);
    void WalkL(int);
    void StepR();
    void StepL();
    void Dead();
    void Reset();
    void ResetGravity();
    int getFlip();
    void setFlip();
    void operator+=(int);
    int getBounce();
signals:


public slots:

private:
    int type;
    QLabel *Pic;
    int x,y;
    int state;
    int TimeCheck;
    int FrameBack;
    double Gravity;
    int dead;
    int bounce,bounceTime;






};

#endif // CHARACTER_H
