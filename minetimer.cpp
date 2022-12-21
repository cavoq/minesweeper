#include "minetimer.h"

MineTimer::MineTimer(QWidget* parent) : QLCDNumber(parent), m_seconds(0)
{
    timer = new QTimer(this);
    time = new QTime(0, 0, 0, 0);
    this->setSegmentStyle(QLCDNumber::Filled);
    display("00:00");
}

MineTimer::~MineTimer()
{
    delete time;
    delete timer;
}

void MineTimer::start()
{
    reset();
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MineTimer::update));
    timer->start(1000);
}

QString MineTimer::getTime()
{
    return time->addSecs(m_seconds).toString("mm:ss");
}

void MineTimer::reset()
{
    timer = new QTimer(this);
    time->setHMS(0, 0, 0, 0);
    display("00:00");
    m_seconds = 0;
}

void MineTimer::stop()
{
    delete timer;
}

void MineTimer::pause()
{
    timer->stop();
}

void MineTimer::resume()
{
    timer->start(1000);
}

void MineTimer::update()
{
    ++m_seconds;
    QString text = time->addSecs(m_seconds).toString("mm:ss");
    display(text);
}
