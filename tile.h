#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <QStateMachine>
#include <QState>

class Tile : public QPushButton
{

public:

    Tile(unsigned int row, unsigned int column, QWidget* parent = nullptr);

    unsigned int row() const;
    unsigned int column() const;

    bool isMine() const;
    bool isFlagged() const;
    bool isRevealed() const;
    bool isUnrevealed() const;

    unsigned int adjacentMineCount() const;
    unsigned int adjacentFlaggedCount() const;

    void addNeighbor(Tile* tile);
    void placeMine(bool val);
    QList<Tile*>& neighbors();

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual QSize sizeHint() const override;

    static QIcon blankIcon();
    static QIcon flagIcon();
    static QIcon mineIcon();
    static QIcon explosionIcon();


public slots:

    void incrementAdjacentFlaggedCount();
    void decrementAdjacentFlaggedCount();

signals:

    void leftClicked();
    void rightClicked();
    void middleClicked();
    void detonated();
    void reveal();
    void revealed();
    void revealNeighbors();
    void flagged(bool);
    void unFlagged(bool);
    void disable();

private:

    void createStateMachine();

private:

    const unsigned int m_row, m_column;
    const bool m_isMine;

    unsigned int m_adjacentMineCount;
    unsigned int m_adjacentFlaggedCount;

    static const QString unrevealedStyleSheet;
    static const QString revealedStyleSheet;
    static const QString revealedWithNumberStylesheet;

    QState *unrevealedState;
    QState *markedState;
    QState *revealedState;
};

#endif // TILE_H
