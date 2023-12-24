#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"playingwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int DLevel() const;

public slots:
    void on_pushButton_clicked();

signals:
    void pushButtonClicked();  // Declare the signal

private:
    Ui::MainWindow *ui;
    PlayingWindow *playingwindow;

};
#endif // MAINWINDOW_H
