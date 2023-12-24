#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>

#include<qDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked()||ui->radioButton_2->isChecked()||ui->radioButton_3->isChecked()){
        emit pushButtonClicked();  // Emit the signal when the button is clicked
    }
    else {
    QMessageBox::warning(this,"warning","Choose a difficulty level.");
    }
}

int MainWindow::DLevel() const
{
    if (ui->radioButton->isChecked()) {
    return 1;
    } else if (ui->radioButton_2->isChecked()) {
    return 2;
    } else if (ui->radioButton_3->isChecked()) {
    return 3;
    }
}
