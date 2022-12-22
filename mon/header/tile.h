#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <QList>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QMouseEvent>

/**
 * @brief The Tile class is a QPushButton that represents a single tile in a minesweeper game.
 *
 * This class provides functions for managing the state of the tile, such as whether it is a mine,
 * flagged, or revealed. It also provides functions for interacting with the tile, such as
 * placing a mine or revealing the tile.
 */
class Tile : public QPushButton
{
    Q_OBJECT

public:

    /**
     * Constructs a Tile object with the given row, column, width, and parent.
     * @param row The row of the tile.
     * @param column The column of the tile.
     * @param width The width of the tile.
     * @param parent The parent widget of the Tile object.
     */
    Tile(unsigned int row, unsigned int column, unsigned int width, QWidget* parent = nullptr);

    /**
     * Destroys the Tile object.
     */
    ~Tile();

    /**
     * Returns the row of the tile.
     * @return The row of the tile.
     */
    unsigned int row() const;

    /**
     * Returns the column of the tile.
     * @return The column of the tile.
     */
    unsigned int column() const;

    /**
     * Returns the width of the tile.
     * @return The width of the tile.
     */
    unsigned int width();

    /**
     * Returns the height of the tile.
     * @return The height of the tile.
     */
    unsigned int height();

    /**
     * Returns whether the tile is a mine.
     * @return true if the tile is a mine, false otherwise.
     */
    bool isMine() const;

    /**
     * Returns whether the tile is flagged.
     * @return true if the tile is flagged, false otherwise.
     */
    bool isFlagged() const;

    /**
     * Returns whether the tile is revealed.
     * @return true if the tile is revealed, false otherwise.
     */
    bool isRevealed() const;

    /**
     * Returns whether the tile is unrevealed.
     * @return true if the tile is unrevealed, false otherwise.
     */
    bool isUnrevealed() const;

    /**
     * Returns the number of mines adjacent to the tile.
     * @return The number of mines adjacent to the tile.
     */
    unsigned int adjacentMineCount() const;

    /**
     * Returns the number of flagged tiles adjacent to the tile.
     * @return The number of flagged tiles adjacent to the tile.
     */
    unsigned int adjacentFlaggedCount() const;

    /**
     * Adds a neighbor to the tile.
     * @param tile The Tile object to be added as a neighbor.
     */
    void addNeighbor(Tile* tile);

    /**
     * Returns a list of the neighbors of the tile.
     * @return A list of the neighbors of the tile.
     */
    QList<Tile*>& neighbors();

    /**
     * Places a mine on the tile.
     * @param val Indicates whether a mine should be placed on the tile (true) or removed (false).
     */
    void placeMine(bool val);

    /**
     * Handles mouse press events on the tile.
     * @param mousePressEvent The mouse press event.
     */
    virtual void mousePressEvent(QMouseEvent* mousePressEvent) override;

    /**
     * Handles mouse release events on the tile.
     * @param mouseReleaseEvent The mouse release event.
     */
    virtual void mouseReleaseEvent(QMouseEvent* mouseReleaseEvent) override;

    /**
     * Returns an icon for a blank tile.
     * @return An icon for a blank tile.
     */
    QIcon blankIcon();

    /**
     * Returns an icon for a flagged tile.
     * @return An icon for a flagged tile.
     */
    QIcon flagIcon();

    /**
     * Returns an icon for a mine tile.
     * @return An icon for a mine tile.
     */
    QIcon mineIcon();

    /**
     * Returns an icon for an exploded mine tile.
     * @return An icon for an exploded mine tile.
     */
    QIcon explosionIcon();

public slots:

    /**
     * Increments the number of flagged tiles adjacent to the tile.
     */
    void incrementAdjacentFlaggedCount();

    /**
     * Decrements the number of flagged tiles adjacent to the tile.
     */
    void decrementAdjacentFlaggedCount();

    /**
     * Increments the number of mines adjacent to the tile.
     */
    void incrementAdjacentMineCount();

signals:

    /**
     * Emitted when the first click on the tile occurs.
     * @param tile The Tile object that was clicked.
     */
    void firstClick(Tile*);

    /**
     * Emitted when the left mouse button is clicked on the tile.
     */
    void leftClicked();

    /**
     * Emitted when the right mouse button is clicked on the tile.
     */
    void rightClicked();

    /**
     * Emitted when the middle mouse button is clicked on the tile.
     */
    void middleClicked();

    /**
     * Emitted when the tile is detonated.
     */
    void detonated();

    /**
     * Emitted when the tile is revealed.
     */
    void reveal();

    /**
     * Emitted after the tile is revealed.
     */
    void revealed();

    /**
     * Emitted when the neighbors of the tile should be revealed.
     */
    void revealNeighbors();

    /**
     * Emitted when the tile is flagged.
     * @param val Indicates whether the tile should be flagged (true) or unflagged (false).
     */
    void flagged(bool);

    /**
     * Emitted when the tile is unflagged.
     * @param val Indicates whether the tile should be unflagged (true) or flagged (false).
     */
    void unFlagged(bool);

    /**
     * Emitted when the tile should be disabled.
     */
    void disable();

private:

    /**
     * Creates the state machine for the tile.
     */
    void createStateMachine();

    /**
     * Sets the display count for the number of mines adjacent to the tile.
     */
    void setAdjacentDisplayCount();

    /**
     * Returns whether the tile has mines adjacent to it.
     * @return true if the tile has mines adjacent to it, false otherwise.
     */
    bool hasAdjacentMines() const;

private:

    const unsigned int m_row; // The row of the tile
    const unsigned int m_column; // The column of the tile
    unsigned int m_width; // The width of the tile
    bool m_isMine; // Indicates whether the tile is a mine

    unsigned int m_adjacentMineCount; // The number of mines adjacent to the tile
    unsigned int m_adjacentFlaggedCount; // The number of flagged tiles adjacent to the tile

    QList<Tile*> m_neighbors; // The neighbors of the tile
    Qt::MouseButtons m_buttonType; // The type of mouse button that was clicked on the tile
    static bool m_firstClick; // Indicates whether this is the first click on the tile

    static const QString unrevealedStyleSheet; // The style sheet for an unrevealed tile
    static const QString revealedStyleSheet; // The style sheet for a revealed tile
    static const QString revealedWithNumberStylesheet; // The style sheet for a revealed tile with a number

    QStateMachine stateMachine; // The state machine for the tile
    QState *unrevealedState; // The unrevealed state of the tile
    QState *flaggedState; // The flagged state of the tile
    QState *revealedState; // The revealed state of the tile
    QState *revealNeighborsState; // The state for revealing the neighbors of the tile
    QFinalState *disabledState; // The disabled state of the tile
};

#endif // TILE_H
