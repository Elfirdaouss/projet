#include "MyFunctions.h"
#include "playingwindow.h"
#include <ctime>
#include <algorithm>
#include <QObject>
#include<QPropertyAnimation>
#include<QTimer>
#include<QObject>
#include<QLabel>
#include<QDebug>
#include<QThread>
using namespace std;

void MyFunctions::myshuffle(QVector<Cart>&v) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::random_shuffle(v.begin(),v.end());
    bool done = false;
    do {
        if (v[0].getNumber()!=v[1].getNumber()&&v[0].getNumber()!=v[2].getNumber()&&v[0].getNumber()!=v[3].getNumber()&&
            v[1].getNumber()!=v[2].getNumber()&&v[1].getNumber()!=v[3].getNumber()&&
            v[2].getNumber()!=v[3].getNumber())
            done = true;
        else
            std::random_shuffle(v.begin(),v.end());
    } while (!done);
}

void MyFunctions::numeration(QVector<Cart>&v){
    int n;
    for (int i=0;i<v.size();++i){
        if(i<10)
            n=i+1;
        else if((i+1)%10==0)
            n=10;
        else
            n=(i+1)%10;
        //ignorance de 8et 9
        switch(n){
            case 8:
                n=10;
                break;
            case 9:
                n=11;
                break;
            case 10:
                n=12;
                break;
        }

        v[i].setNumber(n);
    }
}

void MyFunctions::put_table(QVector<Cart>&v,PlayingWindow& p,Ui::PlayingWindow ui){
    p.updateImageSize(ui.Tcard_2,QString::fromStdString(v[0].getLink()));
    p.updateImageSize(ui.Tcard_3,QString::fromStdString(v[1].getLink()));
    p.updateImageSize(ui.Tcard_4,QString::fromStdString(v[2].getLink()));
    p.updateImageSize(ui.Tcard_8,QString::fromStdString(v[3].getLink()));
}
void MyFunctions::giv_player(QVector<Cart>&v,QVector<Cart>&vp,PlayingWindow& p,Ui::PlayingWindow ui,int& c,int& score){
    for(int i=c;i<c+3;i++){
        Cart cart(v[i].getNumber(),v[i].getLink());
        vp.push_back(cart);
    }
    p.updateButtonIcon(ui.pushButton_1, QString::fromStdString(vp[0].getLink()));
    p.updateButtonIcon(ui.pushButton_2, QString::fromStdString(vp[1].getLink()));
    p.updateButtonIcon(ui.pushButton_3, QString::fromStdString(vp[2].getLink()));

    if(find_ronda(vp)){
        score++;
        p.setTemporaryTextAndColor(ui.Pscore,"you got a \nRONDA  \n+1",'p',score);
    }
    if(find_trenda(vp)){
        score+=5;
        p.setTemporaryTextAndColor(ui.Pscore,"you got a \nRONDA  \n+5",'p',score);
    }
}
void MyFunctions::giv_computer(QVector<Cart>&v,QVector<Cart>&vc,PlayingWindow& p,Ui::PlayingWindow ui,int& c,int& score){
    for(int i=c+3;i<c+6;i++){
        Cart cart(v[i].getNumber(),v[i].getLink());
        vc.push_back(cart);
    }
    if(find_ronda(vc)){
        score++;
        p.setTemporaryTextAndColor(ui.Cscore,"you got a \nRONDA  \n+1",'c',score);
    }
    if(find_trenda(vc)){
        score+=5;
        p.setTemporaryTextAndColor(ui.Cscore,"you got a \nRONDA  \n+5",'c',score);
    }
}
bool MyFunctions::find_ronda(QVector<Cart>&v){
    if(v[0].getNumber()==v[1].getNumber()||v[0].getNumber()==v[2].getNumber()||v[1].getNumber()==v[2].getNumber())
        return true;
    else
        return false;
}
bool MyFunctions::find_trenda(QVector<Cart>&v){
        if(v[0].getNumber()==v[1].getNumber()&&v[0].getNumber()==v[2].getNumber())
            return true;
        else
            return false;
}
void MyFunctions::player_turn(PlayingWindow& p, Ui::PlayingWindow& ui,int& Pscore,int& Cscore,QVector<Cart>& v,QVector<Cart>& pv,QVector<Cart>&cv,int dl) {
        connect(ui.pushButton_1, &QPushButton::clicked, [this](bool) { emit buttonClicked(1); });
        connect(ui.pushButton_2, &QPushButton::clicked, [this](bool) { emit buttonClicked(2); });
        connect(ui.pushButton_3, &QPushButton::clicked, [this](bool) { emit buttonClicked(3); });

        // Rest of your player_turn logic...
        connect(ui.pushButton_1, &QPushButton::clicked, [this,&p, &ui,&Pscore,&Cscore,&cv,dl]() {
            qDebug() << "Button clicked!";
            QString buttonLink = ui.pushButton_1->property("ImagePath").toString();
            int num = buttonLink.midRef(buttonLink.indexOf('_') + 1, 2).toInt();

            check_win(num, p, ui,Pscore,'p');
            p.updateButtonIcon(ui.pushButton_1, "");
            ui.pushButton_1->setEnabled(false);
            QCoreApplication::processEvents();
            QThread::msleep(500);
            switch (dl){
            case 1:
                play_easy(p,ui,cv,Cscore);
                break;
            case 2:
                play_medium(p,ui,cv,Cscore);
                break;
            case 3:
                play_hard(p,ui,cv,Cscore);
                break;
            }
        });
        connect(ui.pushButton_2, &QPushButton::clicked, [this,&p, &ui,&Pscore,&Cscore,&cv,dl]() {
            qDebug() << "Button clicked!";
            QString buttonLink = ui.pushButton_2->property("ImagePath").toString();
            int num = buttonLink.midRef(buttonLink.indexOf('_') + 1, 2).toInt();

            check_win(num, p, ui,Pscore,'p');
            p.updateButtonIcon(ui.pushButton_2, "");
            ui.pushButton_2->setEnabled(false);
            QCoreApplication::processEvents();
            QThread::msleep(500);
            switch (dl){
            case 1:
                play_easy(p,ui,cv,Cscore);
                break;
            case 2:
                play_medium(p,ui,cv,Cscore);
                break;
            case 3:
                play_hard(p,ui,cv,Cscore);
                break;
            }
        });
        connect(ui.pushButton_3, &QPushButton::clicked, [this,&p, &ui,&Pscore,&Cscore,&cv,dl]() {
            qDebug() << "Button clicked!";
            QString buttonLink = ui.pushButton_3->property("ImagePath").toString();
            int num = buttonLink.midRef(buttonLink.indexOf('_') + 1, 2).toInt();

            check_win(num, p, ui,Pscore,'p');
            p.updateButtonIcon(ui.pushButton_3, "");
            ui.pushButton_3->setEnabled(false);
            QCoreApplication::processEvents();
            QThread::msleep(500);
            switch (dl){
            case 1:
                play_easy(p,ui,cv,Cscore);
                break;
            case 2:
                play_medium(p,ui,cv,Cscore);
                break;
            case 3:
                play_hard(p,ui,cv,Cscore);
                break;
            }
        });
        if(cv.empty()){
            emit roundDone();
        }
}

void MyFunctions::check_win(int num,PlayingWindow& p,Ui::PlayingWindow& ui,int& sco,char ch) {
        int x=num;
        if(num>10)
            x=num%10;
        if(num%10==0)
            x=10;
        if(x==p.img_label_num(ui.Tcard_1)){
            p.updateImageSize(ui.Tcard_1,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_2)){
            p.updateImageSize(ui.Tcard_2,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_3)){
            p.updateImageSize(ui.Tcard_3,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_4)){
            p.updateImageSize(ui.Tcard_4,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_5)){
            p.updateImageSize(ui.Tcard_5,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_6)){
            p.updateImageSize(ui.Tcard_6,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_7)){
            p.updateImageSize(ui.Tcard_7,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_8)){
            p.updateImageSize(ui.Tcard_8,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_9)){
            p.updateImageSize(ui.Tcard_9,"");
            score_update(sco,ch,p,ui);
        }
        else if(x==p.img_label_num(ui.Tcard_10)){
            p.updateImageSize(ui.Tcard_10,"");
            score_update(sco,ch,p,ui);
        }
        else
            no_win(p,ui,num);
}
void MyFunctions::score_update(int& sco,char ch,PlayingWindow& p,Ui::PlayingWindow& ui){
        sco+=2;
        if(ch=='p'){
            p.setTemporaryTextAndColor(ui.Pscore,"you got a\n\n+2",ch,sco);
        }
        else
            p.setTemporaryTextAndColor(ui.Cscore,"you got a\n\n+2",ch,sco);
}

void MyFunctions::no_win(PlayingWindow& p,Ui::PlayingWindow& ui,int n){
        if(ui.Tcard_1->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_1,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_1,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_2->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_2,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_2,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_3->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_3,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_3,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_4->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_4,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_4,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_5->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_5,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_5,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_6->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_6,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_6,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_7->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_7,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_7,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_8->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_8,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_8,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_9->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_9,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_9,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
        else if(ui.Tcard_10->property("ImagePath").toString()==""){
            if(n<10)
                p.updateImageSize(ui.Tcard_10,QString::fromStdString(":/cards/MyImgs/cart_0"+to_string(n)+".gif"));
            else
                p.updateImageSize(ui.Tcard_10,QString::fromStdString(":/cards/MyImgs/cart_"+to_string(n)+".gif"));
        }
}
void MyFunctions::play_easy(PlayingWindow& p,Ui::PlayingWindow& ui,QVector<Cart>& cv, int& Cscore) {
        char ch='c';
        srand(static_cast<unsigned int>(std::time(nullptr)));
        int randomIndex = std::rand() % cv.size();
        qDebug() << cv[randomIndex].getNumber()<<QString::fromStdString(cv[randomIndex].getLink());
        QString link =QString::fromStdString(cv[randomIndex].getLink());
        int num = link.midRef(link.indexOf('_') + 1, 2).toInt();
        check_win(num,p,ui,Cscore,ch);
        cv.remove(randomIndex);
}
void MyFunctions::play_medium(PlayingWindow& p,Ui::PlayingWindow& ui,QVector<Cart>& cv, int& Cscore){
        char ch='c';
        int T[10]={p.img_label_num(ui.Tcard_1),
                     p.img_label_num(ui.Tcard_2),
                     p.img_label_num(ui.Tcard_3),
                     p.img_label_num(ui.Tcard_4),
                     p.img_label_num(ui.Tcard_5),
                     p.img_label_num(ui.Tcard_6),
                     p.img_label_num(ui.Tcard_7),
                     p.img_label_num(ui.Tcard_8),
                     p.img_label_num(ui.Tcard_9),
                     p.img_label_num(ui.Tcard_10)};
        bool found = false;
        for (int i = cv.size() - 1; i >= 0; i--) {
            QString link = QString::fromStdString(cv[i].getLink());
            int num = link.midRef(link.indexOf('_') + 1, 2).toInt();
            for (int j = 0; j < 10; j++) {
                if (num == T[j]) {
                    check_win(num, p, ui, Cscore, ch);
                    cv.remove(i);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if(!found){
            QString link =QString::fromStdString(cv[0].getLink());
            int num = link.midRef(link.indexOf('_') + 1, 2).toInt();
            check_win(num,p,ui,Cscore,ch);
            cv.remove(0);
        }
}
void MyFunctions::play_hard(PlayingWindow& p,Ui::PlayingWindow& ui,QVector<Cart>& cv, int& Cscore){

        for (int i = 0; i < cv.size() - 1; i++) {
            if (cv[i].getNumber() < cv[i + 1].getNumber()) {
                swap(cv[i], cv[i + 1]);
            }
        }
        char ch='c';
        int T[10]={p.img_label_num(ui.Tcard_1),
                     p.img_label_num(ui.Tcard_2),
                     p.img_label_num(ui.Tcard_3),
                     p.img_label_num(ui.Tcard_4),
                     p.img_label_num(ui.Tcard_5),
                     p.img_label_num(ui.Tcard_6),
                     p.img_label_num(ui.Tcard_7),
                     p.img_label_num(ui.Tcard_8),
                     p.img_label_num(ui.Tcard_9),
                     p.img_label_num(ui.Tcard_10)};
        bool found = false;
        for (int i = cv.size() - 1; i >= 0; i--) {
            QString link = QString::fromStdString(cv[i].getLink());
            int num = link.midRef(link.indexOf('_') + 1, 2).toInt();
            for (int j = 0; j < 10; j++) {
                if (num == T[j]) {
                    check_win(num, p, ui, Cscore, ch);
                    cv.remove(i);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if(!found){
            QString link =QString::fromStdString(cv[cv.size()-1].getLink());
            int num = link.midRef(link.indexOf('_') + 1, 2).toInt();
            check_win(num,p,ui,Cscore,ch);
            cv.remove(cv.size()-1);
        }
}


