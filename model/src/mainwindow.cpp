#include "model/header/mainwindow.h"
#include "model/header/stats.h"
#include "ui_mainwindow.h"

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


void MainWindow::closeEvent(QCloseEvent *event)
{
    stats->save();
    QMainWindow::closeEvent(event);
}

void MainWindow::setupMenus()
{
    settings = new Settings(this);
    stats = new Stats(this);
    help = new Help(this);

    stats->read();

    connect(ui->actionChangeGameSize, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionShowStats, SIGNAL(triggered()), stats, SLOT(show()));
    connect(ui->actionHelp, SIGNAL(triggered()), help, SLOT(show()));

    connect(settings, SIGNAL(settingsChanged()), this, SLOT(initializeGame()), Qt::UniqueConnection);

    connect(ui->btnNewGame, &QPushButton::clicked, this, &MainWindow::startNewGame, Qt::UniqueConnection);
    connect(ui->btnPauseContinue, &QPushButton::toggled, [this](bool checked)
    {
        if (checked)
        {
            ui->mineTimer->pause();
            gameBoard->hide();
            return;
        }
        ui->mineTimer->resume();
        gameBoard->show();
    });
}

void MainWindow::initializeGame()
{
    delete gameBoard;
    gameBoard = new GameBoard(this, settings);

    ui->mineCounter->setCounter(settings->numMines());
    ui->mineTimer->reset();

    ui->flagCounter->reset();
    ui->flagCounter->setColor(Qt::white);

    connect(gameBoard, &GameBoard::initialized, this, &MainWindow::startGame, Qt::UniqueConnection);
    connect(gameBoard, &GameBoard::flagCountChanged, [this](int flagCount)
    {
        ui->flagCounter->setCounter(flagCount);
        if (flagCount > ui->mineCounter->getCount())
        {
            ui->flagCounter->setColor(Qt::red);
            return;
        }
        ui->flagCounter->setColor(Qt::blue);
    });
    connect(gameBoard, &GameBoard::victory, this, &MainWindow::victory, Qt::UniqueConnection);
    connect(gameBoard, &GameBoard::defeat, this, &MainWindow::defeat, Qt::UniqueConnection);

    int width = this->width() < gameBoard->width() ? gameBoard->width() : this->width();
    int height = this->height() < gameBoard->height() ? gameBoard->height() : this->height();
    this->resize(QSize(width, height));

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
        connect(ui->btnQuit, SIGNAL(clicked()), gameBoard, SLOT(quit()), Qt::UniqueConnection);
        connect(settings, &Settings::settingsChanged, this, &MainWindow::startNewGame);
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
