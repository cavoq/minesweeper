#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QIntValidator>
#include <QMessageBox>

namespace DEFAULT_SETTINGS
{
    const unsigned int MIN_ROWS = 5;
    const unsigned int MIN_COLUMNS = 5;
    const unsigned int MIN_MINES = 1;

    const unsigned int MAX_ROWS = 30;
    const unsigned int MAX_COLUMNS = 40;

    const unsigned int DEFAULT_ROWS = 15;
    const unsigned int DEFAULT_COLUMNS = 20;
    const unsigned int DEFAULT_MINES = 50;
}

namespace Ui { class Settings; }

/**
* @brief The Settings class is a QDialog that allows the user to change the number of rows, columns, and mines in a Minesweeper game.
* It provides functions to retrieve the current values of these settings and emit a signal when they are changed.
*/
class Settings : public QDialog
{
    Q_OBJECT

public:

    /**
    * Constructs a Settings dialog with the given parent.
    * The number of rows, columns, and mines is set to the default values.
    * @param parent The parent widget.
    */
    explicit Settings(QWidget *parent = nullptr);

    /**
     * Constructs a Settings dialog with the given number of rows, columns, and mines and the given parent.
     * @param numRows The number of rows.
     * @param numColumns The number of columns.
     * @param numMines The number of mines.
     * @param parent The parent widget.
     */
    Settings(unsigned int numRows, unsigned int numColumns, unsigned int numMines, QWidget *parent = nullptr);

    /**
     * Destructor for `Settings`.
     */
    ~Settings();

    /**
     * Returns the current number of rows.
     * @return The current number of rows.
     */
    unsigned int numRows();

    /**
     * Returns the current number of columns.
     * @return The current number of columns.
     */
    unsigned int numColumns();

    /**
     * Returns the current number of mines.
     * @return The current number of mines.
     */
    unsigned int numMines();

signals:

    /**
    * This signal is emitted when the settings are changed.
    */
    void settingsChanged();

public slots:

    /**
    * Confirms the changes to the settings and closes the dialog.
    */
    void confirm();
    /**
     * Cancels the changes to the settings and closes the dialog.
     */
    void cancel();

private:

    /**
     * The user interface for the settings window.
     */
    Ui::Settings *ui;

    /**
    * The current number of rows.
    */
    unsigned int m_numRows;

    /**
     * The current number of columns.
     */
    unsigned int m_numColumns;

    /**
     * The current number of mines.
     */
    unsigned int m_numMines;
};

#endif // SETTINGS_H
