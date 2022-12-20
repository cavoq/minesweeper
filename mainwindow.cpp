#include "mainwindow.h"
#include "stats.h"
#include "ui_mainwindow.h"
#include "minetimer.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new Settings(this);
    stats = new Stats(this);
    help = new Help(this);

    connect(ui->actionChangeGameSize, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionShowStats, SIGNAL(triggered()), stats, SLOT(show()));
    connect(ui->actionHelp, SIGNAL(triggered()), help, SLOT(show()));

    connect(ui->btnNewGame, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(ui->btnPauseContinue, &QPushButton::toggled, [this](bool checked)
    {
        if (checked)
        {
            ui->mineTimer->pause();
            return;
        }
        ui->mineTimer->resume();
    });
    connect(settings, SIGNAL(settingsChanged()), this, SLOT(startGame()));
    startGame();
}

MainWindow::~MainWindow()
{
    delete gameBoard;
    delete settings;
    delete ui;
}

void MainWindow::startGame()
{
    delete gameBoard;
    gameBoard = new GameBoard(this, settings);
    gameBoard->show();

    ui->mineCounter->setCounter(settings->numMines());
    ui->flagCounter->reset();
    ui->mineTimer->start();

    connect(gameBoard, SIGNAL(flagCountChanged(uint)), ui->flagCounter, SLOT(setCounter(uint)));
}
