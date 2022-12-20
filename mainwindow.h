#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"
#include "help.h"
#include "settings.h"
#include "stats.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void startGame();
    void updateSettings();

private:

    Ui::MainWindow *ui;
    GameBoard *gameBoard;
    Settings *settings;
    Stats *stats;
    Help *help;

    QStateMachine* m_machine;
    QState* unstartedState;
    QState* inProgressState;
    QState* victoryState;
    QState* defeatState;

    Tile* firstClicked;
};
#endif // MAINWINDOW_H
