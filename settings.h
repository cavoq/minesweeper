#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
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

private:

    Ui::Settings *ui;
    GameBoard *gameBoard;
};

#endif // SETTINGS_H
