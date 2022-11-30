#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QFrame>

class GameBoard : public QFrame
{
    Q_OBJECT

public:

    GameBoard(unsigned int numRows, unsigned int numColumns, unsigned int numMines, QWidget* parent = nullptr);

    unsigned int numRows();
    unsigned int numColumns();
    unsigned int numMines();

    bool setNumRows(unsigned int numRows);
    bool setNumColumns(unsigned int numColumns);
    bool setNumMines(unsigned int numMines);

private:

    bool validMineCount(unsigned int numRows, unsigned int numColumns, unsigned int numMines);

private:

    const unsigned int MIN_ROWS = 10;
    const unsigned int MIN_COLUMNS = 10;

    unsigned int m_numRows;
    unsigned int m_numColumns;
    unsigned int m_numMines;
};

#endif // GAMEBOARD_H
