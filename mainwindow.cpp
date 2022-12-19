#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minetimer.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameBoard = new GameBoard(this, 15, 20, 50);
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
}

MainWindow::~MainWindow()
{
    delete gameBoard;
    delete settings;
    delete ui;
}
