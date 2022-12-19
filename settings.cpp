#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent):
    QDialog(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);

    m_numRows = DEFAULT_SETTINGS::DEFAULT_ROWS;
    m_numColumns = DEFAULT_SETTINGS::DEFAULT_COLUMNS;
    m_numMines = DEFAULT_SETTINGS::DEFAULT_MINES;

    ui->lineEditHeight->setText(QString::number(m_numRows));
    ui->lineEditWidth->setText(QString::number(m_numColumns));
    ui->lineEditMineCount->setText(QString::number(m_numMines));

    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
}

Settings::~Settings()
{
    delete ui;
}

unsigned int Settings::numRows()
{
    return m_numRows;
}

unsigned int Settings::numColumns()
{
    return m_numColumns;
}

unsigned int Settings::numMines()
{
    return m_numMines;
}

void Settings::confirm()
{

    int numRows = ui->lineEditHeight->text().toInt();
    if (numRows < DEFAULT_SETTINGS::MIN_ROWS || numRows > DEFAULT_SETTINGS::MAX_ROWS)
    {
        QMessageBox::warning(this, tr("Ungültige Eingabe"), tr("Die Anzahl der Zeilen ist ungültig. Sie muss zwischen %1 und %2 (inklusive) liegen.").
                             arg(DEFAULT_SETTINGS::MIN_ROWS).arg(DEFAULT_SETTINGS::MAX_ROWS));
        return;
    }

    int numColumns = ui->lineEditWidth->text().toInt();
    if (numColumns < DEFAULT_SETTINGS::MIN_COLUMNS || numColumns > DEFAULT_SETTINGS::MAX_COLUMNS)
    {
        QMessageBox::warning(this, tr("Ungültige Eingabe"), tr("Die Anzahl der Spalten ist ungültig. Sie muss zwischen %1 und %2 (inklusive) liegen.").
                             arg(DEFAULT_SETTINGS::MIN_COLUMNS).arg(DEFAULT_SETTINGS::MAX_COLUMNS));
        return;
    }

    int numMines = ui->lineEditMineCount->text().toInt();
    if (numMines >= numRows * numColumns)
    {
        QMessageBox::warning(this, tr("Ungültige Minenanzahl"), tr("Die Anzahl der Minen muss kleiner als die Anzahl der Zeilen mal die Anzahl der Spalten sein."));
        return;
    }

    m_numRows = numRows;
    m_numColumns = numColumns;
    m_numMines = numMines;

    emit settingsChanged();

    this->close();
}

void Settings::cancel()
{
    this->close();
}
