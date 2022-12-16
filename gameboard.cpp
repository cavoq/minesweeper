#include "gameboard.h"

#include <algorithm>
#include <random>

#include <QGridLayout>
#include <QSpacerItem>
#include <QSet>

GameBoard::GameBoard(QWidget* parent, unsigned int numRows, unsigned int numColumns, unsigned int numMines): QFrame(parent)
{
    if (!validMineCount(numRows, numColumns, numMines))
        throw std::invalid_argument("Invalid game board settings");
    setupLayout();
    createTiles();
    addNeighbors();
}

bool GameBoard::validMineCount(unsigned int numRows, unsigned int numColums, unsigned int numMines)
{
    return numMines < numRows * numColums;
}

bool GameBoard::setNumMines(unsigned int numMines)
{
    if (!validMineCount(m_numMines, m_numColumns, numMines))
        return false;
    m_numMines = numMines;
    return true;
}

bool GameBoard::setNumRows(unsigned int numRows)
{
    if (numRows < boardsize::MIN_ROWS || !validMineCount(numRows, m_numColumns, m_numMines))
        return false;
    m_numRows = numRows;
    return true;
}

bool GameBoard::setNumColumns(unsigned int numColumns)
{
    if (numColumns < boardsize::MIN_COLUMNS || !validMineCount(m_numRows, numColumns, m_numMines))
        return false;
    m_numColumns = numColumns;
    return true;
}

void GameBoard::setupLayout()
{
    this->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    auto layout = new QGridLayout;

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    this->setLayout(layout);
}

void GameBoard::createTiles()
{
    for (unsigned int row = 0; row < m_numRows; ++row)
    {
        m_tiles += QList<Tile*>{};
        for (unsigned int column = 0; column < m_numColumns; ++column)
        {
            m_tiles[row] += new Tile(row, column, this);
            //static_cast<QGridLayout*>(this->layout())->addWidget(m_tiles[row][column], row, column);
            connect(m_tiles[row][column], &Tile::firstClick, this, &GameBoard::placeMines);
            connect(m_tiles[row][column], &Tile::flagged, [this, tile = m_tiles[row][column]](bool isMine)
            {
                if (isMine)
                    m_correctFlags.insert(tile);
                else
                    m_incorrectFlags.insert(tile);
                checkVictory();
            });
            connect(m_tiles[row][column], &Tile::unFlagged, [this, tile = m_tiles[row][column]](bool isMine)
            {
                if (isMine)
                    m_correctFlags.remove(tile);
                else
                    m_incorrectFlags.remove(tile);
                checkVictory();
            });
            connect(m_tiles[row][column], &Tile::revealed, [this, tile = m_tiles[row][column]]()
            {
                m_revealedTiles.insert(tile);
                checkVictory();
            });
            connect(this, &GameBoard::defeat, m_tiles[row][column], &Tile::disable);
            connect(this, &GameBoard::victory, m_tiles[row][column], &Tile::disable);
        }
    }
    //m_tiles[0][0]->setDown(true);
}

void GameBoard::addNeighbors()
{
    for (unsigned int row = 0; row < m_numRows; ++row)
    {
        for (unsigned int column = 0; column < m_numColumns; ++column)
        {
            Tile* tile = m_tiles[row][column];
            unsigned int lastRow = m_numRows - 1;
            unsigned int lastColumn = m_numColumns - 1;

            if (row && column)                          tile->addNeighbor(m_tiles[row - 1][column - 1]);
            if (row)                                    tile->addNeighbor(m_tiles[row - 1][column]);
            if (row && column < lastColumn)             tile->addNeighbor(m_tiles[row - 1][column + 1]);
            if (column < lastColumn)                    tile->addNeighbor(m_tiles[row][column + 1]);
            if (row < lastRow && column < lastColumn)	tile->addNeighbor(m_tiles[row + 1][column + 1]);
            if (row < lastRow)                          tile->addNeighbor(m_tiles[row + 1][column]);
            if (row < lastRow && column)                tile->addNeighbor(m_tiles[row + 1][column - 1]);
            if (column)                                 tile->addNeighbor(m_tiles[row][column - 1]);
        }
    }
}

void GameBoard::checkVictory()
{
    if (!m_victory)
    {
        emit flagCountChanged(m_correctFlags.size() + m_incorrectFlags.size());
        if ((m_revealedTiles.size() == m_numColumns * m_numRows - m_numMines) && m_incorrectFlags.isEmpty())
        {
            emit victory();
            m_victory = true;
        }
    }
}

void GameBoard::placeMines(Tile* firstClicked)
{
    QList<Tile*> tiles;
    QSet<Tile*> doneUse;
    doneUse += firstClicked;
    for (Tile* neighbor: firstClicked->neighbors())
    {
        doneUse += neighbor;
    }

    for (unsigned int row = 0; row < m_numRows; ++row)
    {
        m_tiles += QList<Tile*>{};
        for (unsigned int column = 0; column < m_numColumns; ++column)
        {
            if (Tile *tile = m_tiles[row][column]; !doneUse.contains(tile))
                tiles += tile;
        }
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(tiles.begin(), tiles.end(), generator);

    for (unsigned int i = 0; i < m_numMines; ++i)
    {
        tiles[i]->placeMine(true);
        m_mines.insert(tiles[i]);
    }

    emit initialized();
}
