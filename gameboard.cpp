#include "gameboard.h"

GameBoard::GameBoard(QWidget* parent, unsigned int numRows, unsigned int numColumns, unsigned int numMines): QFrame(parent)
{
    if (!validMineCount(numRows, numColumns, numMines)) {
        throw std::invalid_argument("Invalid game board settings");
    }
}

bool GameBoard::validMineCount(unsigned int numRows, unsigned int numColums, unsigned int numMines)
{
    return numMines < numRows*numColums;
}

bool GameBoard::setNumMines(unsigned int numMines)
{
    if (!validMineCount(m_numMines, m_numColumns, numMines)) {
        return false;
    }
    m_numMines = numMines;
    return true;
}

bool GameBoard::setNumRows(unsigned int numRows)
{
    if (numRows < boardsize::MIN_ROWS || !validMineCount(numRows, m_numColumns, m_numMines)) {
        return false;
    }
    m_numRows = numRows;
    return true;
}

bool GameBoard::setNumColumns(unsigned int numColumns)
{
    if (numColumns < boardsize::MIN_COLUMNS || !validMineCount(m_numRows, numColumns, m_numMines)) {
        return false;
    }
    m_numColumns = numColumns;
    return true;
}
