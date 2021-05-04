/*
 * Program: FinalProject - Game Value Calculator
 * Author: Daniel Meeker
 * Date: 5/4/21
 *
 * This program allows the user to enter the UPC information
 * of a video game and returns the value of the game based on
 * if the game is loose (cartridge or disc only), complete-in-box,
 * or still factory sealed. It saves the price information for each
 * game while the program is running and comes up with a total value
 * of all the games entered.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "loosegame.h"
#include "completegame.h"
#include "sealedgame.h"

vector<LooseGame> looseGames;
vector<CompleteGame> completeGames;
vector<SealedGame> sealedGames;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DatabaseConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::getPrice
 * This function queries the database and populates
 * the output fields of the GUI with the results
 */
void MainWindow::getPrice() {
    QSqlQuery query;
    if (ui->looseButton->isChecked()) {
        query.prepare("Select loose, console, game FROM priceguide WHERE upc = :upc");
        query.bindValue(":upc", ui->upcInput->text().toLongLong());
        if(!query.exec())
                qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

            if(query.first())
                ui->priceOutput->setText(query.value(0).toString());
            else
                ui->priceOutput->setText("game not found");
            if(query.first())
                ui->consoleOutput->setText(query.value(1).toString());
            else
                ui->consoleOutput->setText("game not found");
            if(query.first())
                ui->gameOutput->setText(query.value(2).toString());
            else
                ui->gameOutput->setText("game not found");

            //Exception handling preventing users from adding bad data to collection
            if (ui->gameOutput->text() == "game not found" || ui->priceOutput->text() == "") {
                ui->addButton->setEnabled(false);
            }
            else {
                ui->addButton->setEnabled(true);
            }

    }
    if (ui->completeButton->isChecked()) {
        query.prepare("Select cib, console, game FROM priceguide WHERE upc = :upc");
        query.bindValue(":upc", ui->upcInput->text().toLongLong());
        if(!query.exec())
                qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

            if(query.first())
                ui->priceOutput->setText(query.value(0).toString());
            else
                ui->priceOutput->setText("game not found");
            if(query.first())
                ui->consoleOutput->setText(query.value(1).toString());
            else
                ui->consoleOutput->setText("game not found");
            if(query.first())
                ui->gameOutput->setText(query.value(2).toString());
            else
                ui->gameOutput->setText("game not found");

            //Exception handling preventing users from adding bad data to collection
            if (ui->gameOutput->text() == "game not found" || ui->priceOutput->text() == "") {
                ui->addButton->setEnabled(false);
            }
            else {
                ui->addButton->setEnabled(true);
            }

    }

    if (ui->sealedButton->isChecked()) {
        query.prepare("Select new, console, game FROM priceguide WHERE upc = :upc");
        query.bindValue(":upc", ui->upcInput->text().toLongLong());
        if(!query.exec())
                qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

            if(query.first())
                ui->priceOutput->setText(query.value(0).toString());
            else
                ui->priceOutput->setText("game not found");
            if(query.first())
                ui->consoleOutput->setText(query.value(1).toString());
            else
                ui->consoleOutput->setText("game not found");
            if(query.first())
                ui->gameOutput->setText(query.value(2).toString());
            else
                ui->gameOutput->setText("game not found");

            //Exception handling preventing users from adding bad data to collection
            if (ui->gameOutput->text() == "game not found" || ui->priceOutput->text() == "") {
                ui->addButton->setEnabled(false);
            }
            else {
                ui->addButton->setEnabled(true);
            }


    }


}

/**
 * @brief MainWindow::addItem
 * This function adds items to the collection, which is made up of 3 different vectors
 * one for loose games, one for complete games, and one for sealed games
 */
void MainWindow::addItem() {
    string priceToConvert = ui->priceOutput->text().toLocal8Bit().toStdString();
    priceToConvert = priceToConvert.substr(1); //drop the $ so that it can convert to a double
    string name = ui->gameOutput->text().toLocal8Bit().toStdString();
    string console = ui->consoleOutput->text().toLocal8Bit().toStdString();
    double price = stod(priceToConvert);
    long long upc = ui->upcInput->text().toLongLong();
    if (ui->looseButton->isChecked()) {
        looseGames.push_back(LooseGame(price, name, console, upc));
        //ui->totalValueOutput->setText("$" + QString::number(price));
    }
    if (ui->completeButton->isChecked()) {
        completeGames.push_back(CompleteGame(price, name, console, upc));
        //ui->totalValueOutput->setText("$" + QString::number(price));
    }
    if (ui->sealedButton->isChecked()) {
        sealedGames.push_back(SealedGame(price, name, console, upc));
        //ui->totalValueOutput->setText("$" + QString::number(price));
    }
    calculateTotalValue();
    ui->addButton->setEnabled(false); // prevents accidentally adding game twice
    clearForm();
}

/**
 * @brief MainWindow::calculateTotalValue
 * This function iterates through the vectors to calculate the total price of each vector
 * it then adds the three vectors together to get the final total
 */
void MainWindow::calculateTotalValue() {
    double runningTotal = 0;
    double looseTotal = 0;
    double completeTotal = 0;
    double sealedTotal = 0;

    auto iter1 = looseGames.begin();
    for (; iter1 < looseGames.end(); iter1++) {
        looseTotal += iter1[0].getPrice();
    }
    auto iter2 = completeGames.begin();
    for (; iter2 != completeGames.end(); iter2++) {
        completeTotal += iter2[0].getPrice();
    }
    auto iter3 = sealedGames.begin();
    for (; iter3 != sealedGames.end(); iter3++) {
        sealedTotal += iter3[0].getPrice();
    }
    runningTotal = looseTotal + completeTotal + sealedTotal;
ui->looseTotalOutput->setText("$" + QString::number(looseTotal));
ui->completeTotalOutput->setText("$" + QString::number(completeTotal));
ui->sealedTotalOutput->setText("$" + QString::number(sealedTotal));
ui->totalValueOutput->setText("$" + QString::number(runningTotal));
}

/**
 * @brief MainWindow::clearForm
 * This function clears the output fields of the form, but not the collection values outputs
 * it also resets the focus to the UPC input for ease of use.
 */
void MainWindow::clearForm() {
    ui->upcInput->setText("");
    ui->consoleOutput->setText("");
    ui->priceOutput->setText("");
    ui->gameOutput->setText("");
    ui->upcInput->setFocus();
    ui->addButton->setEnabled(false);

}

/**
 * @brief MainWindow::clearCollection
 * This function loops through each vector and pops
 * off each element to reset each vector to a blank slate
 */
void MainWindow::clearCollection() {
    for (size_t i = 0; i < looseGames.size(); i++) {
        looseGames.pop_back();
    }
    for (size_t i = 0; i < completeGames.size(); i++) {
        completeGames.pop_back();
    }
    for (size_t i = 0; i < sealedGames.size(); i++) {
        sealedGames.pop_back();
    }
    calculateTotalValue(); //refreshes the value outputs
}

/**
 * @brief MainWindow::DatabaseConnect
 * This function connects the program to the database file.
 * For the program to work the db.setDatabaseName() must include
 * the complete path to where the database is saved on your computer.
 */
void MainWindow::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName("C:/Users/danie/OneDrive/Desktop/Homework/Advanced C++/gameprices.db");
        //db.setDatabaseName("complete path to database on your computer")

        if(!db.open())
            qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";
}
