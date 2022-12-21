#ifndef MINETIMER_H
#define MINETIMER_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

/**
* @brief The MineTimer class is a QLCDNumber widget that displays a timer in the format "HH:MM:SS".
* It provides functions to start, pause, resume, and reset the timer.
*/
class MineTimer : public QLCDNumber
{
    Q_OBJECT

public:

    /**
    * @brief Constructs a MineTimer widget with the given parent.
    * @param parent The parent widget.
    */
    MineTimer(QWidget* parent = nullptr);

    /**
     * Destructor for `MineTimer`.
     */
    ~MineTimer();

    /**
     * Returns the current time displayed by the timer in the format "HH:MM:SS".
     * @return The current time displayed by the timer.
     */
    QString getTime();

    /**
     * Resets the timer to 0.
     */
    void reset();

    /**
     * Pauses the timer.
     */
    void pause();

    /**
     * Stops the timer and resets it to 0.
     */
    void stop();

    /**
     * Resumes the timer if it was previously paused.
     */
    void resume();

public slots:

    /**
    * Starts the timer.
    */
    void start();

private slots:

    /**
    * Updates the time displayed by the timer.
    */
    void update();

private:

    /**
    * The number of seconds elapsed since the timer was started.
    */
    int m_seconds;

    /**
     * A QTime object used to keep track of the elapsed time.
     */
    QTime *time;

    /**
     * A QTimer object that updates the time displayed by the timer every second.
     */
    QTimer *timer;
};

#endif // MINETIMER_H
