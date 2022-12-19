#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QFrame>
#include <QList>
#include <QSet>
#include "qgridlayout.h"
#include "settings.h"
#include "tile.h"

class GameBoard : public QFrame
{
    Q_OBJECT

public:

    GameBoard(QWidget* parent = nullptr, Settings *settings = new Settings());
    ~GameBoard();

    unsigned int numRows();
    unsigned int numColumns();
    unsigned int numMines();
    void initialize();

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

    QGridLayout *gameLayout;
    Settings *settings;
    static int DEFAULT_TILE_WIDTH;

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
