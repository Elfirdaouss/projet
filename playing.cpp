#include "playing.h"
#include "ui_playing.h"

Playing::Playing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Playing)
{
    ui->setupUi(this);
}

Playing::~Playing()
{
    delete ui;
}
