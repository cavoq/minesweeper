#ifndef COUNTER_H
#define COUNTER_H

#include <QLCDNumber>

/**
 * @class Counter
 * @brief The Counter class is a subclass of QLCDNumber that displays a counter value and allows for resetting the counter.
 *
 * The Counter class is a subclass of QLCDNumber, which is a Qt widget that displays a number in LCD-style digits.
 * The Counter class adds functionality to display a counter value and reset the counter. It also allows for setting the color of the displayed counter value.
 */
class Counter : public QLCDNumber
{
    Q_OBJECT

public:

    /**
     * @brief Constructs a Counter object with the given parent widget. If parent is nullptr, the counter will be a top-level widget.
     * @param parent The parent widget of the counter. If nullptr, the counter will be a top-level widget.
     */
    Counter(QWidget* parent = nullptr);

    /**
     * @brief Returns the current value of the counter.
     * @return The current value of the counter.
     */
    int getCount();

    /**
     * @brief Sets the color of the displayed counter value to the specified color.
     * @param col The color to set the counter value to.
     */
    void setColor(QColor col);

public slots:

    /**
     * @brief Sets the value of the counter to the specified count.
     * @param count The value to set the counter to.
     */
    void setCounter(uint count);

    /**
     * @brief Resets the counter to 0.
     */
    void reset();

private:

    /**
     * Current count.
     */
    int count;
};

#endif // COUNTER_H
