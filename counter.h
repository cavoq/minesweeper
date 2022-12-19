#ifndef COUNTER_H
#define COUNTER_H

#include <QLCDNumber>

class Counter : public QLCDNumber
{
    Q_OBJECT

public:

    Counter(QWidget* parent = nullptr);

public slots:

    void setCounter(uint count);
    void reset();

private:

    int count;
};

#endif // COUNTER_H
