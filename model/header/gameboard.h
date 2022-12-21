#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QFrame>
#include <QList>
#include <QSet>
#include "qgridlayout.h"
#include "settings.h"
#include "tile.h"

/**
 * @class GameBoard
 * @brief The GameBoard class represents a two-dimensional grid of tiles and provides methods for interacting with the game board.
 *
 * The GameBoard class is a subclass of QFrame, which is a Qt widget used for building graphical user interfaces.
 * It represents a two-dimensional grid of tiles, where each tile can either contain a mine or not.
 * The class provides methods for accessing information about the game board, such as the number of rows, columns, and mines.
 * It also has methods for initializing the game board and placing mines on the game board.
 * The GameBoard class also has slots and signals that can be used to communicate with other objects in the Qt framework.
 */
class GameBoard : public QFrame
{
    Q_OBJECT

public:

    /**
     * Constructs a new game board with the given parent widget and settings.
     * @param parent the parent widget
     * @param settings the game settings
     */
    GameBoard(QWidget* parent = nullptr, Settings *settings = new Settings());

    /**
     * Destructor for GameBoard.
     */
    ~GameBoard();

    /**
     * Returns the number of rows on the game board.
     * @return the number of rows
     */
    unsigned int numRows();

    /**
     * Returns the number of columns on the game board.
     * @return the number of columns
     */
    unsigned int numColumns();

    /**
     * Returns the number of mines on the game board.
     * @return the number of mines
     */
    unsigned int numMines();

    /**
     * Initializes the game board. This should be called before the game begins.
     */
    void initialize();

public slots:

    /**
     * Places mines on the game board, avoiding the given tile.
     * @param firstClicked the tile that was clicked first and should not contain a mine
     */
    void placeMines(Tile* firstClicked);

    /**
     * Quits the game.
     */
    void quit();

signals:

    /**
     * Emitted when the game board has finished initialization.
     */
    void initialized();

    /**
     * Emitted when the player has won the game.
     */
    void victory();

    /**
     * Emitted when the player has lost the game.
     */
    void defeat();

    /**
     * Emitted when the number of flagged tiles has changed.
     * @param flagCount the new number of flagged tiles
     */
    void flagCountChanged(unsigned int flagCount);

private:

    /**
     * Returns true if the given number of mines is valid for the given number of rows and columns.
     * @param numRows the number of rows
     * @param numColumns the number of columns
     * @param numMines the number of mines
     * @return true if the number of mines is valid, false otherwise
     */
    bool validMineCount(unsigned int numRows, unsigned int numColumns, unsigned int numMines);

    /**
     * Calculates the size of each tile based on the number of rows, columns, and the size of the game board.
     */
    void calculateTileSize();

    /**
     * Creates the tiles for the game board.
     */
    void createTiles();

    /**
     * Sets up the layout for the game board.
     */
    void setupLayout();

    /**
     * Adds the neighboring tiles to each tile on the game board.
     */
    void addNeighbors();

    /**
     * Checks if the player has won the game. If the player has won, victory() is emitted.
     */
    void checkVictory();

    /**
     * Performs the animation for when the player loses the game.
     */
    void defeatAnimation();;

private:

    /**
     * The layout manager for the game board.
     */
    QGridLayout *gameLayout;

    /**
     * The game settings.
     */
    Settings *settings;

    /**
     * The default width of each tile.
     */
    static int DEFAULT_TILE_WIDTH;

    /**
     * The number of rows on the game board.
     */
    unsigned int m_numRows;

    /**
     * The number of columns on the game board.
     */
    unsigned int m_numColumns;

    /**
     * The number of mines on the game board.
     */
    unsigned int m_numMines;

    /**
     * The width of each tile.
     */
    unsigned int tileWidth;

    /**
     * A 2D list of pointers to the tiles on the game board.
     */
    QList<QList<Tile*>> m_tiles;

    /**
     * A set of pointers to the tiles that contain mines.
     */
    QSet<Tile*> m_mines;

    /**
     * A set of pointers to tiles that have been correctly flagged as containing a mine.
     */
    QSet<Tile*> m_correctFlags;

    /**
     * A set of pointers to tiles that have been incorrectly flagged as containing a mine.
     */
    QSet<Tile*> m_incorrectFlags;

    /**
     * A set of pointers to tiles that have been revealed.
     */
    QSet<Tile*> m_revealedTiles;

    /**
     * A timer used for the defeat animation.
     */
    QTimer* explosionTimer;

    /**
     * Whether the player has lost the game.
     */
    bool m_defeat = false;

    /**
     * Whether the player has won the game.
     */
    bool m_victory = false;
};

#endif // GAMEBOARD_H
