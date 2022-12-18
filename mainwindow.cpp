#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qInfo()<<ui->mainFrame->width();
    gameBoard = new GameBoard(this, 15, 20, 50);
    gameBoard->show();
    settings = new Settings(gameBoard, this);
    connect(ui->actionChangeGameSize, SIGNAL(triggered()), settings, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete gameBoard;
    delete settings;
    delete ui;
}
