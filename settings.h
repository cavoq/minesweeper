#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QIntValidator>
#include <QMessageBox>

namespace DEFAULT_SETTINGS
{
    const unsigned int MIN_ROWS = 2;
    const unsigned int MIN_COLUMNS = 2;

    const unsigned int MAX_ROWS = 30;
    const unsigned int MAX_COLUMNS = 40;

    const unsigned int DEFAULT_ROWS = 15;
    const unsigned int DEFAULT_COLUMNS = 20;
    const unsigned int DEFAULT_MINES = 50;
}

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:

    explicit Settings(QWidget *parent = nullptr);
    Settings(unsigned int numRows, unsigned int numColumns, unsigned int numMines, QWidget *parent = nullptr);
    ~Settings();

    unsigned int numRows();
    unsigned int numColumns();
    unsigned int numMines();

signals:
    void settingsChanged();

public slots:

    void confirm();
    void cancel();

private:

    Ui::Settings *ui;
    unsigned int m_numRows;
    unsigned int m_numColumns;
    unsigned int m_numMines;
};

#endif // SETTINGS_H
