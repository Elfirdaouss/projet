#include "playingwindow.h"
#include "ui_playingwindow.h"

#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include<QString>
#include<QThread>
#include<QPushButton>


PlayingWindow::PlayingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayingWindow)
{
    ui->setupUi(this);
}

PlayingWindow::~PlayingWindow()
{
    delete ui;
}

void PlayingWindow::updateImageSize(QLabel* label, const QString& imagePath)
{
    int w=160;
    int h=250;
    QPixmap LT1(imagePath);
    label->setPixmap(LT1.scaled(w,h, Qt::KeepAspectRatio));
    label->setProperty("ImagePath", imagePath);
    QCoreApplication::processEvents();
    QThread::msleep(500);
}
void PlayingWindow::setTemporaryTextAndColor(QLabel *label, const QString &text,char Char,int sco)
{
    // Store the original properties
    QString originalStyleSheet = label->styleSheet();

    // Set temporary text
    label->setText(text);

    // Set temporary background color
    label->setStyleSheet("background-color: #aa55ff;color:#ffffff;font: 14pt Segoe UI;");  // Fix: Use six or eight characters3123

    // Create a QTimer to revert changes after a certain time
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [label, originalStyleSheet,Char,sco,timer,this]() {
        // Revert to original text and background color
        if(Char=='p')
            label->setText("Player Score\n\n"+QString::number(sco));
        if(Char=='c')
            label->setText("Computer\n\nScore\n\n"+QString::number(sco));
        label->setStyleSheet(originalStyleSheet);
        disconnect(timer);
        timer->deleteLater();
    });

    timer->start(2000);
}
void PlayingWindow::updateButtonIcon(QPushButton* button, const QString& link){
    button->setIcon(QIcon(link));
    button->setIconSize(QSize(180,270));
    button->setProperty("ImagePath",link);
    QCoreApplication::processEvents();
    QThread::msleep(500);
}

int PlayingWindow::img_label_num(QLabel *label){
    QString labelLink= label->property("ImagePath").toString();
    int num=labelLink.midRef(labelLink.indexOf('_')+1,2).toInt();
    if(num<=10)
        return num;
    else if(num%10==0)
        return 10;
    else
        return num%10;
}
