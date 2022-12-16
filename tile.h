#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <QList>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QMouseEvent>

class Tile : public QPushButton
{
    Q_OBJECT

public:

    Tile(unsigned int row, unsigned int column, QWidget* parent = nullptr);
    ~Tile();

    unsigned int row() const;
    unsigned int column() const;

    bool isMine() const;
    bool isFlagged() const;
    bool isRevealed() const;
    bool isUnrevealed() const;

    unsigned int adjacentMineCount() const;
    unsigned int adjacentFlaggedCount() const;

    void addNeighbor(Tile* tile);
    QList<Tile*>& neighbors();
    void placeMine(bool val);

    virtual void mousePressEvent(QMouseEvent* mousePressEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent* mouseReleaseEvent) override;

    static QIcon blankIcon();
    static QIcon flagIcon();
    static QIcon mineIcon();
    static QIcon explosionIcon();

public slots:

    void incrementAdjacentFlaggedCount();
    void decrementAdjacentFlaggedCount();
    void incrementAdjacentMineCount();

signals:

    void firstClick(Tile*);
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
    void setAdjacentDisplayCount();

private:

    const unsigned int m_row, m_column;
    bool m_isMine;

    unsigned int m_adjacentMineCount;
    unsigned int m_adjacentFlaggedCount;

    QList<Tile*> m_neighbors;
    Qt::MouseButtons m_buttonType;
    static bool m_firstClick;

    static const QString unrevealedStyleSheet;
    static const QString revealedStyleSheet;
    static const QString revealedWithNumberStylesheet;

    QStateMachine stateMachine;
    QState *unrevealedState;
    QState *flaggedState;
    QState *revealedState;
    QState *revealNeighborsState;
    QFinalState *disabledState;
};

#endif // TILE_H
