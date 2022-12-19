#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minetimer.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameBoard = new GameBoard(this);
    gameBoard->show();
    settings = new Settings(gameBoard, this);
    connect(ui->actionChangeGameSize, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->btnNewGame, SIGNAL(clicked()), ui->mineTimer, SLOT(start()));
    connect(ui->btnPauseContinue, &QPushButton::toggled, [this](bool checked)
    {
        if (checked)
        {
            ui->mineTimer->pause();
            return;
        }
        ui->mineTimer->resume();
    });
    connect(gameBoard, SIGNAL(flagCountChanged(uint)), ui->flagCounter, SLOT(setCounter(uint)));
}

MainWindow::~MainWindow()
{
    delete gameBoard;
    delete settings;
    delete ui;
}
