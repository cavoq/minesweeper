#include "settings.h"
#include "ui_settings.h"

Settings::Settings(GameBoard* gameBoard, QWidget *parent):
    QDialog(parent), ui(new Ui::Settings),
    gameBoard(gameBoard)
{
    ui->setupUi(this);

    ui->lineEditHeight->setText(QString::number(gameBoard->numRows()));
    ui->lineEditWidth->setText(QString::number(gameBoard->numColumns()));
    ui->lineEditMineCount->setText(QString::number(gameBoard->numMines()));

    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::confirm()
{

    int numRows = ui->lineEditHeight->text().toInt();
    if (numRows < boardsize::MIN_ROWS || numRows > boardsize::MAX_ROWS)
    {
        QMessageBox::warning(this, tr("Ungültige Eingabe"), tr("Die Anzahl der Zeilen ist ungültig. Sie muss zwischen %1 und %2 (inklusive) liegen.").arg(boardsize::MIN_ROWS).arg(boardsize::MAX_ROWS));
        return;
    }

    int numColumns = ui->lineEditWidth->text().toInt();
    if (numColumns < boardsize::MIN_COLUMNS || numColumns > boardsize::MAX_COLUMNS)
    {
        QMessageBox::warning(this, tr("Ungültige Eingabe"), tr("Die Anzahl der Spalten ist ungültig. Sie muss zwischen %1 und %2 (inklusive) liegen.").arg(boardsize::MIN_COLUMNS).arg(boardsize::MAX_COLUMNS));
        return;
    }

    int numMines = ui->lineEditMineCount->text().toInt();
    if (numMines >= numRows * numColumns)
    {
        QMessageBox::warning(this, tr("Ungültige Minenanzahl"), tr("Die Anzahl der Minen muss kleiner als die Anzahl der Zeilen mal die Anzahl der Spalten sein."));
        return;
    }

    delete gameBoard;
    gameBoard = new GameBoard(this->parentWidget(), numRows, numColumns, numMines);
    gameBoard->show();

    this->close();
}

void Settings::cancel()
{
    this->close();
}
