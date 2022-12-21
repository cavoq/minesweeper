#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
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

protected:

    void closeEvent(QCloseEvent *event) override;

signals:

    void startGame();
    void startNewGame();
    void victory();
    void defeat();

protected slots:

    void onFinished(bool win);
    void initializeGame();

private:

    void setupMenus();
    void setupStateMachine();

private:

    Ui::MainWindow *ui;
    QVBoxLayout *layout;
    GameBoard *gameBoard;
    Settings *settings;
    Stats *stats;
    Help *help;

    QStateMachine* stateMachine;
    QState* unstartedState;
    QState* inProgressState;
    QState* victoryState;
    QState* defeatState;

    Tile* firstClicked;
};
#endif // MAINWINDOW_H
