#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <vector>
#include "platform.h"
#include "pf_normal.h"
#include "pf_spike.h"
#include "pf_flip.h"
#include "pf_left.h"
#include "pf_right.h"
#include "pf_string.h"
#include "pf_ufox.h"
#include "pf_ufoy.h"
#include <ctime>
#include "character.h"
#include <QPixmap>
#include <QKeyEvent>
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include "entername.h"
#include <fstream>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetGameMode(int,int,int);
public slots:
    void GameLoop();
protected:
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
signals:
    void OpenIntro();
private:
    Ui::MainWindow *ui;
    int GameMode;
    int Time;
    int HP1,MP1;
    int HP2,MP2;
    std::vector<Platform*> P_Vector;

    int speed;
    int p1;
    int p2;
    int stage;
    Character *Char1;
    Character *Char2;
    int p1_state,p1_state_tmp,p1_step_on,p1_step_on_tmp;
    int p2_state,p2_state_tmp,p2_step_on,p2_step_on_tmp;
    int p1_step_on_time;
    int p2_step_on_time;
    int press_right,press_left;
    int press_c,press_z;
    double Gravity_1,Gravity_2;
    int p1_record,p2_record;
    int p1_dead,p2_dead;
    int Difficulty;
    int Pause;
    int Mute;
    int bgm_track;
    void GameReset();
    Platform *get_platform();
    QMediaPlayer bgm,gameover_sound,death_sound,spiked_sound;
    bool CheckHigh(int);
};
#endif // MAINWINDOW_H
