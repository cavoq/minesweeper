#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QFrame>
#include <QList>
#include <QSet>
#include "tile.h"

namespace boardsize
{
    const unsigned int MIN_ROWS = 10;
    const unsigned int MIN_COLUMNS = 10;

    const unsigned int DEFAULT_ROWS = 20;
    const unsigned int DEFAULT_COLUMNS = 20;
    const unsigned int DEFAULT_MINES = 10;

    const unsigned int DEFAULT_TILE_WIDTH = 20;
}

class GameBoard : public QFrame
{
    Q_OBJECT

public:

    GameBoard(QWidget* parent = nullptr, unsigned int numRows = boardsize::DEFAULT_ROWS, unsigned int numColumns = boardsize::DEFAULT_COLUMNS,
              unsigned int numMines = boardsize::DEFAULT_MINES);

    unsigned int numRows();
    unsigned int numColumns();
    unsigned int numMines();

    bool setNumRows(unsigned int numRows);
    bool setNumColumns(unsigned int numColumns);
    bool setNumMines(unsigned int numMines);

public slots:

    void placeMines(Tile* firstClicked);

signals:

    void initialized();
    void victory();
    void defeat();
    void flagCountChanged(unsigned int flagCount);

private:

    bool validMineCount(unsigned int numRows, unsigned int numColumns, unsigned int numMines);
    void calculateTileSize();
    void createTiles();
    void setupLayout();
    void addNeighbors();
    void checkVictory();

private:

    unsigned int m_numRows;
    unsigned int m_numColumns;
    unsigned int m_numMines;
    unsigned int tileWidth;

    QList<QList<Tile*>> m_tiles;
    QSet<Tile*> m_mines;
    QSet<Tile*> m_correctFlags;
    QSet<Tile*> m_incorrectFlags;
    QSet<Tile*> m_revealedTiles;

    bool m_defeat = false;
    bool m_victory = false;
};

#endif // GAMEBOARD_H
