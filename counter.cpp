#include "counter.h"

Counter::Counter(QWidget* parent) : QLCDNumber(parent), count(0)
{
    setDigitCount(3);
}

void Counter::setCounter(uint count)
{
    if (count <= 0 || count > 999)
        return;
    display((int)count);
}

void Counter::reset()
{
    count = 0;
    display(count);
}
