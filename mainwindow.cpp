#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new Settings(this);
    connect(ui->actionChangeGameSize, SIGNAL(triggered()), settings, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
