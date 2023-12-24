#include "mainwindow.h"
#include"playingwindow.h"
#include"ui_playingwindow.h"
#include"cart.h"
#include"MyFunctions.h"

#include <QApplication>
#include <QVector>
#include<QDebug>
#include <cstdlib>
#include <ctime>
#include <QThread>
#include <QCoreApplication>
#include <QEventLoop>

using namespace std;
void play(MyFunctions& myFunctions,PlayingWindow& p, Ui::PlayingWindow& ui,int& Pscore,int& Cscore,QVector<Cart>& v,QVector<Cart>& pv,QVector<Cart>&cv,int dl){
    static int c=4;
    if(c<40){
    myFunctions.giv_player(v,pv,p,ui,c,Pscore);
    myFunctions.giv_computer(v,cv,p,ui,c,Cscore);
    myFunctions.player_turn(p,ui,Pscore,Cscore,v,pv,cv,dl);
        pv.clear();
        c+=6;
    play(myFunctions,p,ui,Pscore,Cscore,v,pv,cv,dl);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    PlayingWindow playingWindow;
    MyFunctions myFunctions;
    QVector<Cart> carts;
    QVector<Cart> CompCarts;
    QVector<Cart> PlayerCarts;
    Ui::PlayingWindow ui;
    ui.setupUi(&playingWindow);
    int times_conunter=4,Pscore=0,Cscore=0;


    mainWindow.setWindowTitle("RONDA GAME");
    mainWindow.setWindowIcon(QIcon(":/icon/MyImgs/Myicon.jpg"));
    // Populate the QVector with 40 Cart objects
    for (int i = 1; i <= 40; ++i) {
        string link;
        if(i<10){
            link =":/cards/MyImgs/cart_0"+to_string(i)+".gif";
            }
        else
            link = ":/cards/MyImgs/cart_" + to_string(i)+".gif";
        Cart cart(i, link);
        carts.push_back(cart);
    }
    //giving nmbs
    myFunctions.numeration(carts);
    myFunctions.myshuffle(carts);

    // Connect the signal from MainWindow to a slot in main.cpp
    QObject::connect(&mainWindow, &MainWindow::pushButtonClicked, &mainWindow,[&]() {

        int DL = mainWindow.DLevel();//level of difficulty 1:easy 2:medium 3:hard
        mainWindow.hide();
        playingWindow.setWindowTitle("RONDA GAME");
        playingWindow.setWindowIcon(QIcon(":/icon/MyImgs/Myicon.jpg"));
        playingWindow.showMaximized();

        playingWindow.updateImageSize(ui.label,":/cards/MyImgs/back.gif");
        QCoreApplication::processEvents();
        QThread::msleep(1000);
        myFunctions.put_table(carts,playingWindow,ui);


        play(myFunctions,playingWindow,ui,Pscore,Cscore,carts,PlayerCarts,CompCarts,DL);




    });
    mainWindow.show();



    return a.exec();
}
