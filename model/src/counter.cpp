#include "model/header/counter.h"

Counter::Counter(QWidget* parent) : QLCDNumber(parent), count(0)
{
    setDigitCount(3);
}

int Counter::getCount()
{
    return count;
}

void Counter::setCounter(uint count)
{
    this->count = count;
    if (count > 999)
        return;
    display((int)count);
}

void Counter::setColor(QColor col)
{
    QPalette pal = this->palette();
    pal.setColor(QPalette::WindowText, col);
    this->setPalette(pal);
}

void Counter::reset()
{
    count = 0;
    display((int)count);
}
