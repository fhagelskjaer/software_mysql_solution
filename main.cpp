#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("frhag");  // Change to username
    db.setPassword("password");  // Change to password
    db.open();
    
    QSqlQuery query;
    
    qDebug() << query.exec("SELECT * FROM task"); // employee er her navnet på en tabel, ikke et schema
    
    qDebug() << "Number of rows:" << query.size(); 
    
    while (query.next()) {
        int id = query.value(0).toInt();
        QString description = query.value(1).toString();
        int time = query.value(2).toInt();
        qDebug() << "id:" << id << "description:" << description << "time:" << time;
        }
    
    query.prepare("INSERT INTO task (description, time)"
                  "VALUES (:description, :time)");
                  
    query.bindValue(":description", argv[1]);
    query.bindValue(":time", std::stoi(argv[2]));
    
    qDebug() << query.exec();
    
    qDebug() << "Finished";
    return 1;
}


