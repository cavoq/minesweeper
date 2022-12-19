#ifndef MINETIMER_H
#define MINETIMER_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class MineTimer : public QLCDNumber
{
    Q_OBJECT

public:

    MineTimer(QWidget* parent = nullptr);
    void reset();
    void pause();
    void resume();

public slots:

    void start();

private slots:

    void update();

private:

    int m_seconds;
    QTime *time;
    QTimer *timer;
};

#endif // MINETIMER_H