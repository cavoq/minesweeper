#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "mon/header/gameboard.h"
#include "help.h"
#include "settings.h"
#include "stats.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class is the main window of the game, and provides the interface for starting and playing the game.
 *
 * The MainWindow class is a subclass of QMainWindow, which is a Qt widget used for building main windows in GUI applications. It provides the interface for starting and playing the game, and includes a menu bar, game board, and other widgets for displaying game information and settings. The class has a public constructor for creating a new `MainWindow` object, and a public destructor for cleaning up when the object is no longer needed. The class also has a `closeEvent` method that is called when the window is closed, and several slots and signals for communicating with other objects in the Qt framework.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * Constructs a new `MainWindow` with the given parent widget.
     * @param parent the parent widget
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * Destructor for `MainWindow`.
     */
    ~MainWindow();

protected:

    /**
     * Reimplementation of the `closeEvent` method from QMainWindow. This method is called when the window is closed.
     * @param event the close event
     */
    void closeEvent(QCloseEvent *event) override;

signals:

    /**
     * Emitted when the game should be started.
     */
    void startGame();

    /**
     * Emitted when a new game should be started.
     */
    void startNewGame();

    /**
     * Emitted when the player has won the game.
     */
    void victory();

    /**
     * Emitted when the player has lost the game.
     */
    void defeat();

protected slots:

    /**
     * Called when the game has finished.
     * @param win true if the player won the game, false if the player lost
     */
    void onFinished(bool win);

    /**
     * Initializes the game.
     */
    void initializeGame();

private:

    /**
     * Sets up the menus for the main window.
     */
    void setupMenus();

    /**
     * Sets up the state machine for the main window.
     */
    void setupStateMachine();

private:

    /**
     * The user interface for the main window.
     */
    Ui::MainWindow *ui;

    /**
     * The layout manager for the main window.
     */
    QVBoxLayout *layout;

    /**
     * The game board for the main window.
     */
    GameBoard *gameBoard;

    /**
     * The game settings for the main window.
     */
    Settings *settings;

    /**
     * The game statistics for the main window.
     */
    Stats *stats;

    /**
     * The help dialog for the main window.
     */
    Help *help;

    /**
     * The state machine for the main window.
     */
    QStateMachine* stateMachine;

    /**
     * The state for when the game has not yet started.
     */
    QState* unstartedState;

    /**
     * The state for when the game is in progress.
     */
    QState* inProgressState;

    /**
     * The state for when the player has won the game.
     */
    QState* victoryState;

    /**
     * The state for when the player has lost the game.
     */
    QState* defeatState;
};

#endif // MAINWINDOW_H
