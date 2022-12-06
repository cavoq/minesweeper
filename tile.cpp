#include "tile.h"

Tile::Tile(unsigned int row, unsigned int column, QWidget* parent):
    QPushButton(parent), m_row(row), m_column(column), m_isMine(false),
    m_adjacentMineCount(0), m_adjacentFlaggedCount(0)
{
    createStateMachine();
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCheckable(true);
    setMouseTracking(true);
}

unsigned int Tile::row() const
{
    return m_row;
}

unsigned int Tile::column() const
{
    return m_column;
}

bool Tile::isMine() const
{
    return m_isMine;
}

const QString Tile::unrevealedStyleSheet =
        "Tile"
        "{"
        "	border: 1px solid darkgray;"
        "	background: qradialgradient(cx : 0.4, cy : -0.1, fx : 0.4, fy : -0.1, radius : 1.35, stop : 0 #fff, stop: 1 #bbb);"
        "	border - radius: 1px;"
        "}";
const QString Tile::revealedStyleSheet =
        "Tile"
        "{"
        "	border: 1px solid lightgray;"
        "}";
const QString Tile::revealedWithNumberStylesheet =
        "Tile"
        "{"
        "	color: %1;"
        "	font-weight: bold;"
        "	border: 1px solid lightgray;"
        "}";


