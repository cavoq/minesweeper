#include "model/header/tile.h"

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

bool Tile::m_firstClick = false;

Tile::Tile(unsigned int row, unsigned int column, unsigned int width, QWidget* parent):
    QPushButton(parent), m_row(row), m_column(column), m_width(width), m_isMine(false),
    m_adjacentMineCount(0), m_adjacentFlaggedCount(0)
{
    createStateMachine();
    this->setFixedSize(width, width);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCheckable(true);
    setMouseTracking(true);
}

Tile::~Tile()
{
    m_firstClick = false;
    delete unrevealedState;
    delete flaggedState;
    delete revealedState;
    delete disabledState;
    delete revealNeighborsState;
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

bool Tile::isFlagged() const
{
    return stateMachine.configuration().contains(flaggedState);
}

bool Tile::isRevealed() const
{
    return stateMachine.configuration().contains(revealedState);
}

bool Tile::isUnrevealed() const
{
    return stateMachine.configuration().contains(unrevealedState);
}


bool Tile::hasAdjacentMines() const
{
    return m_adjacentMineCount;
}

unsigned int Tile::adjacentMineCount() const
{
    return m_adjacentMineCount;
}

unsigned int Tile::adjacentFlaggedCount() const
{
    return m_adjacentFlaggedCount;
}

void Tile::addNeighbor(Tile* tile)
{
    m_neighbors += tile;
    connect(this, &Tile::revealNeighbors, tile, &Tile::reveal, Qt::QueuedConnection);
}

QList<Tile*>& Tile::neighbors()
{
    return m_neighbors;
}

void Tile::placeMine(bool val)
{
    m_isMine = val;
    for (auto neighbor : m_neighbors)
        neighbor->incrementAdjacentMineCount();
}

void Tile::mousePressEvent(QMouseEvent* mousePressEvent)
{
    if (!m_firstClick)
    {
        m_firstClick = true;
        emit firstClick(this);
    }

    if (mousePressEvent->buttons() == Qt::MiddleButton)
        m_buttonType = Qt::MiddleButton;
    if (mousePressEvent->buttons() == Qt::LeftButton)
        m_buttonType = Qt::LeftButton;
    if (mousePressEvent->buttons() == Qt::RightButton)
        m_buttonType = Qt::RightButton;
}

void Tile::mouseReleaseEvent(QMouseEvent* mouseReleasedEvent)
{
    if (m_buttonType == Qt::LeftButton)
        emit leftClicked();
    else if (m_buttonType == Qt::RightButton)
        emit rightClicked();
    else if (m_buttonType == Qt::MiddleButton)
        emit middleClicked();
}

QIcon Tile::blankIcon()
{
    static QIcon icon = QIcon();
    return icon;
}

QIcon Tile::flagIcon()
{
    QIcon icon = QIcon(QPixmap(":/flag").scaled(QSize(m_width, m_width)));
    return icon;
}

QIcon Tile::mineIcon()
{
    QIcon icon = QIcon(QPixmap(":/mine").scaled(QSize(m_width, m_width)));
    return icon;
}

QIcon Tile::explosionIcon()
{
    QIcon icon = QIcon(QPixmap(":/explosion").scaled(QSize(m_width, m_width)));
    return icon;
}

void Tile::incrementAdjacentFlaggedCount()
{
    m_adjacentFlaggedCount += 1;
}

void Tile::decrementAdjacentFlaggedCount()
{
    m_adjacentFlaggedCount -= 1;
}


void Tile::incrementAdjacentMineCount()
{
    m_adjacentMineCount += 1;
}

void Tile::createStateMachine()
{
    unrevealedState = new QState();
    flaggedState = new QState();
    revealedState = new QState();
    revealNeighborsState = new QState();
    disabledState = new QFinalState();

    unrevealedState->addTransition(this, &Tile::leftClicked, revealedState);
    unrevealedState->addTransition(this, &Tile::rightClicked, flaggedState);
    unrevealedState->addTransition(this, &Tile::reveal, revealedState);
    unrevealedState->addTransition(this, &Tile::disable, disabledState);

    flaggedState->addTransition(this, &Tile::middleClicked, unrevealedState);

    revealNeighborsState->addTransition(this, &Tile::reveal, revealedState);

    connect(unrevealedState, &QState::entered, [this]()
    {
        this->setIcon(blankIcon());
        this->setStyleSheet(unrevealedStyleSheet);
    });

    connect(revealNeighborsState, &QState::entered, [this]()
    {
        if (m_adjacentFlaggedCount == m_adjacentMineCount && m_adjacentMineCount)
            revealNeighbors();
        emit reveal();
    });

    connect(revealedState, &QState::entered, [this]()
    {
        this->setIcon(blankIcon());
        this->setChecked(true);
        if (!isMine())
        {
            this->setAdjacentDisplayCount();
            if (!hasAdjacentMines())
                revealNeighbors();
            emit revealed();
        }
        else
        {
            emit detonated();
            this->setStyleSheet(revealedStyleSheet);
            QPushButton::setText("");
            setIcon(mineIcon());
        }
    });

    connect(flaggedState, &QState::entered, [this]()
    {
        this->setIcon(flagIcon());
        for (Tile *neighbor : m_neighbors)
            neighbor->incrementAdjacentFlaggedCount();
        emit flagged(m_isMine);
    });

    connect(flaggedState, &QState::exited, [this]()
    {
        for (Tile *neighbor : m_neighbors)
            neighbor->decrementAdjacentFlaggedCount();
        emit unFlagged(m_isMine);
    });

    connect(disabledState, &QState::entered, []() {});

    stateMachine.addState(unrevealedState);
    stateMachine.addState(flaggedState);
    stateMachine.addState(revealedState);
    stateMachine.addState(revealNeighborsState);
    stateMachine.addState(disabledState);

    stateMachine.setInitialState(unrevealedState);
    stateMachine.start();
}

void Tile::setAdjacentDisplayCount()
{
    QString color;
        switch (m_adjacentMineCount)
        {
        case 1:
            color = "blue";
            break;
        case 2:
            color = "green";
            break;
        case 3:
            color = "red";
            break;
        case 4:
            color = "midnightblue";
            break;
        case 5:
            color = "maroon";
            break;
        case 6:
            color = "darkcyan";
            break;
        case 7:
            color = "black";
            break;
        case 8:
            color = "grey";
            break;
        default:
            break;
        }

        QPushButton::setStyleSheet(revealedWithNumberStylesheet.arg(color));
        if(m_adjacentMineCount)
            QPushButton::setText(QString::number(m_adjacentMineCount));
}
