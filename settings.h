#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QIntValidator>
#include <QMessageBox>
#include "gameboard.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:

    explicit Settings(GameBoard* gameBoard, QWidget *parent = nullptr);
    ~Settings();

public slots:

    void confirm();
    void cancel();

private:

    Ui::Settings *ui;
    GameBoard *gameBoard;
};

#endif // SETTINGS_H
