#include "stats.h"
#include "qevent.h"
#include "ui_stats.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QString Stats::statsJsonFile = "stats.json";

Stats::Stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stats)
{
    ui->setupUi(this);
    layout = new QVBoxLayout();
    layout->addWidget(ui->statisticsTableWidget);
    this->setLayout(layout);
    createTable();
    read();
}

void Stats::createTable()
{
   ui->statisticsTableWidget->setColumnCount(7);
   QStringList tableHeaders = QStringList{"Zeilenanzahl", "Spaltenanzahl", "Minenanzahl", "Gespielte Spiele", "Siege", "Niederlagen", "Schnellster Sieg"};
   ui->statisticsTableWidget->setHorizontalHeaderLabels(tableHeaders);
}

Stats::~Stats()
{
    delete ui;
}

bool Stats::addToRecord(Settings &settings, QString time, bool win)
{
    int rows = settings.numRows();
    int columns = settings.numColumns();
    int mines = settings.numMines();

    for (int i = 0; i < ui->statisticsTableWidget->rowCount(); ++i)
    {
        if (ui->statisticsTableWidget->item(i, 0)->text().toInt() == rows &&
            ui->statisticsTableWidget->item(i, 1)->text().toInt() == columns &&
            ui->statisticsTableWidget->item(i, 2)->text().toInt() == mines)
        {
            int games = ui->statisticsTableWidget->item(i, 3)->text().toInt() + 1;
            int wins = ui->statisticsTableWidget->item(i, 4)->text().toInt();
            int loses = ui->statisticsTableWidget->item(i, 5)->text().toInt();

            if (win)
            {
                wins++;
            } else
            {
                loses++;
            }

            ui->statisticsTableWidget->item(i, 3)->setText(QString::number(games));
            ui->statisticsTableWidget->item(i, 4)->setText(QString::number(wins));
            ui->statisticsTableWidget->item(i, 5)->setText(QString::number(loses));

            QString currentFastest = ui->statisticsTableWidget->item(i, 6)->text();
            QTime currentFastestTime = QTime::fromString(currentFastest, "mm:ss");
            QTime newTime = QTime::fromString(time, "mm:ss");

            if (newTime < currentFastestTime || currentFastest.isEmpty()) {
                ui->statisticsTableWidget->item(i, 6)->setText(time);
            }
            return true;
        }
    }
    return insertRecord(settings, time, 1, win);
}

bool Stats::insertRecord(Settings &settings, QString time, int games, int wins)
{
    int rows = settings.numRows();
    int columns = settings.numColumns();
    int mines = settings.numMines();
    int loses = games - wins;

    bool recordExists = false;
    for (int i = 0; i < ui->statisticsTableWidget->rowCount(); ++i)
    {
        if (ui->statisticsTableWidget->item(i, 0)->text().toInt() == rows &&
            ui->statisticsTableWidget->item(i, 1)->text().toInt() == columns &&
            ui->statisticsTableWidget->item(i, 2)->text().toInt() == mines)
        {
            ui->statisticsTableWidget->item(i, 3)->setText(QString::number(games));
            ui->statisticsTableWidget->item(i, 4)->setText(QString::number(wins));
            ui->statisticsTableWidget->item(i, 5)->setText(QString::number(loses));
            ui->statisticsTableWidget->item(i, 6)->setText(time);
            recordExists = true;
            break;
        }
    }

    if (!recordExists)
    {
        int row = ui->statisticsTableWidget->rowCount();
        ui->statisticsTableWidget->insertRow(row);
        ui->statisticsTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(rows)));
        ui->statisticsTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(columns)));
        ui->statisticsTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(mines)));
        ui->statisticsTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(games)));
        ui->statisticsTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(wins)));
        ui->statisticsTableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(loses)));
        ui->statisticsTableWidget->setItem(row, 6, new QTableWidgetItem(time));
    }

    return true;
}

bool Stats::read()
{
    QFile file(statsJsonFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open" << statsJsonFile << "for reading.";
        return false;
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray statsArray = doc.array();

    for (int i = 0; i < statsArray.size(); ++i) {
        QJsonObject statsObject = statsArray[i].toObject();
        QJsonObject settingsObject = statsObject["settings"].toObject();

        int rows = settingsObject["rows"].toInt();
        int columns = settingsObject["columns"].toInt();
        int mines = settingsObject["mines"].toInt();
        int games = statsObject["games"].toInt();
        int wins = statsObject["wins"].toInt();
        QString fastest = statsObject["fastest"].toString();

        Settings settings = Settings(rows, columns, mines);
        insertRecord(settings, fastest, games, wins);
    }

    return true;
}
