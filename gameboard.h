#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QFrame>

namespace boardsize
{
    const unsigned int MIN_ROWS = 10;
    const unsigned int MIN_COLUMNS = 10;

    const unsigned int DEFAULT_ROWS = 20;
    const unsigned int DEFAULT_COLUMNS = 20;
    const unsigned int DEFAULT_MINES = 10;
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

private:

    bool validMineCount(unsigned int numRows, unsigned int numColumns, unsigned int numMines);

private:

    unsigned int m_numRows;
    unsigned int m_numColumns;
    unsigned int m_numMines;
};

#endif // GAMEBOARD_H
