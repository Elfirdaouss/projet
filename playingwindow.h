#ifndef PLAYINGWINDOW_H
#define PLAYINGWINDOW_H

#include"playingwindow.h"
#include <QMainWindow>
#include<QLabel>
#include<QTimer>
#include<QPushButton>

namespace Ui {
class PlayingWindow;
}

class PlayingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayingWindow(QWidget *parent = nullptr);
    ~PlayingWindow();
    void updateImageSize(QLabel* label, const QString& imagePath);
    void updateButtonIcon(QPushButton* button, const QString& link);
    void setTemporaryTextAndColor(QLabel *label, const QString &text,char Char,int sco);
    int img_label_num(QLabel *label);
private:
    Ui::PlayingWindow *ui;
};

#endif // PLAYINGWINDOW_H
