#ifndef PLAYING_H
#define PLAYING_H

#include <QDialog>

namespace Ui {
class Playing;
}

class Playing : public QDialog
{
    Q_OBJECT

public:
    explicit Playing(QWidget *parent = nullptr);
    ~Playing();

private:
    Ui::Playing *ui;
};

#endif // PLAYING_H
