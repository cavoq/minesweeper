#include "settings.h"
#include "ui_settings.h"

Settings::Settings(GameBoard* gameBoard, QWidget *parent):
    QDialog(parent), ui(new Ui::Settings),
    gameBoard(gameBoard)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}
