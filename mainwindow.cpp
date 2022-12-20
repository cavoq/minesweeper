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
    setupStateMachine();
    setupMenus();
}

MainWindow::~MainWindow()
{
    delete gameBoard;
    delete settings;
    delete help;
    delete stats;
    delete ui;
}

void MainWindow::setupMenus()
{
    settings = new Settings(this);
    stats = new Stats(this);
    help = new Help(this);

    connect(ui->actionChangeGameSize, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionShowStats, SIGNAL(triggered()), stats, SLOT(show()));
    connect(ui->actionHelp, SIGNAL(triggered()), help, SLOT(show()));

    connect(settings, SIGNAL(settingsChanged()), this, SLOT(initializeGame()));

    connect(ui->btnNewGame, &QPushButton::clicked, this, &MainWindow::startNewGame, Qt::UniqueConnection);
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

void MainWindow::initializeGame()
{
    delete gameBoard;
    gameBoard = new GameBoard(this, settings);

    ui->mineCounter->setCounter(settings->numMines());
    ui->mineTimer->reset();
    ui->flagCounter->reset();

    connect(gameBoard, &GameBoard::initialized, this, &MainWindow::startGame, Qt::UniqueConnection);
    connect(gameBoard, SIGNAL(flagCountChanged(uint)), ui->flagCounter, SLOT(setCounter(uint)));
    connect(gameBoard, &GameBoard::victory, this, &MainWindow::victory, Qt::UniqueConnection);
    connect(gameBoard, &GameBoard::defeat, this, &MainWindow::defeat, Qt::UniqueConnection);

    gameBoard->show();
}

void MainWindow::setupStateMachine()
{
    stateMachine = new QStateMachine();

    unstartedState = new QState();
    inProgressState = new QState();
    victoryState = new QState();
    defeatState = new QState();

    unstartedState->addTransition(this, &MainWindow::startGame, inProgressState);

    inProgressState->addTransition(this, &MainWindow::victory, victoryState);
    inProgressState->addTransition(this, &MainWindow::defeat, defeatState);
    inProgressState->addTransition(this, &MainWindow::startNewGame, unstartedState);

    victoryState->addTransition(this, &MainWindow::startNewGame, unstartedState);
    defeatState->addTransition(this, &MainWindow::startNewGame, unstartedState);

    connect(unstartedState, &QState::entered, [this]()
    {
        initializeGame();
    });

    connect(inProgressState, &QState::entered, [this]()
    {
        ui->mineTimer->start();
    });

    connect(victoryState, &QState::entered, [this]()
    {
        onFinished(true);
    });

    connect(defeatState, &QState::entered, [this]()
    {
        onFinished(false);
    });

    stateMachine->addState(unstartedState);
    stateMachine->addState(inProgressState);
    stateMachine->addState(victoryState);
    stateMachine->addState(defeatState);

    stateMachine->setInitialState(unstartedState);
    stateMachine->start();
}

void MainWindow::onFinished(bool win)
{
    ui->mineTimer->stop();
    QString time = ui->mineTimer->getTime();
    stats->addToRecord(*settings, time, win);
}
