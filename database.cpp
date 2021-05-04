/*
 * This file is deprecated, database functionality has been moved
 * to mainwindow.cpp.
 */
#include "database.h"

Database::Database()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) {
        qWarning() << "ERROR: driver not available";
    }
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("C:/Users/danie/OneDrive/Desktop/Homework/Advanced C++/gameprices");
    if(!db.open()) {
        qWarning() << "ERROR: " << db.lastError();
    }
}

