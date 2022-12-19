#include "counter.h"

Counter::Counter(QWidget* parent) : QLCDNumber(parent), count(0)
{
    setDigitCount(3);
}

void Counter::increment()
{
    ++count;
    display(count);
}

void Counter::decrement()
{
    if (count <= 0)
        return;
    --count;
    display(count);
}

void Counter::reset()
{
    count = 0;
    display(count);
}
