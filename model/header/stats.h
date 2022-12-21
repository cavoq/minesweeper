#ifndef STATS_H
#define STATS_H

#include "settings.h"
#include "qboxlayout.h"
#include <QDialog>

namespace Ui { class Stats; }

/**
 * @brief The Stats class is a QDialog that displays and manages game statistics.
 *
 * This class provides functions for adding a new record to the game statistics, saving the
 * statistics to a JSON file, and reading the statistics from the JSON file. It also has
 * a private function for creating the table that displays the statistics.
 */
class Stats : public QDialog
{
    Q_OBJECT

public:

    /**
     * Constructs a Stats object with the given parent.
     * @param parent The parent widget of the Stats object.
     */
    explicit Stats(QWidget *parent = nullptr);

    /**
     * Destroys the Stats object.
     */
    ~Stats();

    /**
     * Adds a new record to the game statistics.
     * @param settings The game settings of the record being added.
     * @param time The time it took to complete the game in the record being added.
     * @param win Indicates whether the game was won or lost in the record being added.
     * @return true if the record was successfully added, false otherwise.
     */
    bool addToRecord(Settings &settings, QString time, bool win);

    /**
     * Saves the game statistics to a JSON file.
     * @return true if the statistics were successfully saved, false otherwise.
     */
    bool save();

    /**
     * Reads the game statistics from a JSON file.
     * @return true if the statistics were successfully read, false otherwise.
     */
    bool read();

private:

    /**
     * Creates the table that displays the game statistics.
     */
    void createTable();

    /**
     * Inserts a record into the game statistics table.
     * @param settings The game settings of the record being inserted.
     * @param time The time it took to complete the game in the record being inserted.
     * @param games The number of games played with the given settings.
     * @param wins The number of games won with the given settings.
     * @return true if the record was successfully inserted, false otherwise.
     */
    bool insertRecord(Settings &settings, QString time, int games, int wins);

    /**
     * User interface of the stats dialog.
     */
    Ui::Stats *ui;

    /**
     * The layout of the stats object.
     */
    QVBoxLayout *layout;

    /**
     * Static member variable storing the path of the JSON file for the game statistics.
     */
    static QString statsJsonFile;
};

#endif // STATS_H
