#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include"PlayingWindow.h"
#include"ui_playingwindow.h"
#include"Cart.h"

#include<QPixmap>
#include <QVector>
#include<QLabel>
#include<QDebug>
#include<string>


class MyFunctions : public QObject {
    Q_OBJECT
public:
    void myshuffle(QVector<Cart> &v);
    void numeration(QVector<Cart>&v);
    void put_table(QVector<Cart>&v,PlayingWindow& p,Ui::PlayingWindow ui);
    void giv_player(QVector<Cart>&v,QVector<Cart>&vp,PlayingWindow& p,Ui::PlayingWindow ui,int& c,int& score);
    void giv_computer(QVector<Cart>&v,QVector<Cart>&vc,PlayingWindow& p,Ui::PlayingWindow ui,int& c,int& score);
    bool find_ronda(QVector<Cart>&v);
    bool find_trenda(QVector<Cart>&v);
    void showTemporaryMessage(const QString &message, int duration);
    void player_turn(PlayingWindow& p, Ui::PlayingWindow& ui,int& Pscore,int& Cscore,QVector<Cart>& v,QVector<Cart>& pv,QVector<Cart>&cv,int dl);
    void check_win(int num,PlayingWindow& p, Ui::PlayingWindow& ui,int& sco,char ch);
    void score_update(int& sco,char ch,PlayingWindow& p,Ui::PlayingWindow& ui);
    void no_win(PlayingWindow& p,Ui::PlayingWindow& ui,int n);
    void play_easy(PlayingWindow& p,Ui::PlayingWindow& ui,QVector<Cart>& cv,int& Cscore);
    void play_medium(PlayingWindow& p,Ui::PlayingWindow& ui,QVector<Cart>& cv, int& Cscore);
    void play_hard(PlayingWindow& p,Ui::PlayingWindow& ui,QVector<Cart>& cv, int& Cscore);
signals:
    void roundDone();
    void buttonClicked(int num);

};
#endif // MYFUNCTIONS_H
