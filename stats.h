#ifndef STATS_H
#define STATS_H

#include "settings.h"
#include "qboxlayout.h"
#include <QDialog>

namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();
    bool addToRecord(Settings &settings, QString time, bool win);

private:
    void createTable();
    bool read();
    bool insertRecord(Settings &settings, QString time, int games, int wins);

private:
    Ui::Stats *ui;
    QVBoxLayout *layout;
    static QString statsJsonFile;
};

#endif // STATS_H
